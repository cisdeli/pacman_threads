#include "../headers/index.h"
#include "../headers/indexbase.h"

MapController::MapController() {}

MapController::MapController(WINDOW *win, int yWin, int xWin,
                             unsigned int _frameSpeed) {
  // Passa as dimensões e a janela para desenhar nela.
  gameWin = win;
  yMax = yWin;
  xMax = xWin;
  frameSpeed = _frameSpeed;

  map = new Map();
  pacman = new Pacman(3, 1);
  configure();
}

MapController::~MapController() {
  delete map;
  delete pacman;
}

bool MapController::getGameState() { return gameRunning; }

void MapController::print(int c, int y, int x, int cpair) {
  start_color();
  init_pair(1, COLOR_GREEN, COLOR_GREEN);
  init_pair(2, COLOR_YELLOW, COLOR_BLACK);
  init_pair(3, COLOR_BLUE, COLOR_BLACK);
  init_pair(4, COLOR_CYAN, COLOR_BLACK);
  init_pair(5, COLOR_RED, COLOR_BLACK);
  init_pair(6, COLOR_MAGENTA, COLOR_BLACK);

  wattron(gameWin, A_BOLD);
  wattron(gameWin, COLOR_PAIR(cpair));
  mvwaddch(gameWin, y, x, c);
  wattroff(gameWin, COLOR_PAIR(cpair));
  wattroff(gameWin, A_BOLD);
}

void MapController::showScore() {
  mvwprintw(gameWin, 0, xMax / 2 - 5, "{Score: %d}", score);
}

void MapController::configure() {
  // Configure game
  score = 0;
  gameRunning = true;

  // Configure pacman
  pacmanCh = '<';

  // Configure points in the map
  memset(points, -1, sizeof points);
  points[pacmanX][pacmanY] = 1;

  /// Configure Ghosts
  memset(ghostsPosition, 0, sizeof ghostsPosition);
  ghostsCurrPos.push_back({10, 4});
  ghostsCurrPos.push_back({61, 3});
  ghostsCurrPos.push_back({10, 20});
  ghostsCurrPos.push_back({30, 15});

  // Configure semaphore
  sem_init(&ghostMutex, 0, 1); // Binary
}

void MapController::printLine(int i, int j, char c) {
  mvwaddch(gameWin, j + 8, i + xMax / 3 - 8, (int)c);
}

void MapController::generate() {
  int mapX = map->getMapX();
  int mapY = map->getMapY();
  for (int i = 0; i < mapX; i++) {
    for (int j = 0; j < mapY; j++) {
      if (j == pacmanY && i == pacmanX) // Print pacman
        MapController::print((int)pacmanCh, j + 8, i + xMax / 3 - 8, 2);
      else if (ghostsPosition[i][j] == 1) // Print ghost
        for (int k = 0; k < ghostsCurrPos.size(); k++) {
          if (ghostsCurrPos[k].first == i && ghostsCurrPos[k].second == j)
            MapController::print((int)'$', j + 8, i + xMax / 3 - 8, k + 3);
        }
      else if (map->isWallH(j, i)) // Print obstacle
        MapController::print((int)'#', j + 8, i + xMax / 3 - 8, 1);
      else if (map->isWallX(j, i)) // Print free space(without dot)
        printLine(i, j, ' ');
      else if (map->isDot(j, i)) {
        if (points[i][j] == 1) // Print free space(dot was eaten)
          printLine(i, j, ' ');
        else
          printLine(i, j, '.'); // Print dot
      }
    }
  }
}

int MapController::readUserKey() {
  if (gameRunning)
    userKey = wgetch(gameWin); // Pega o input do usuario.
  return userKey;
}

bool MapController::isPacDead() {
  return checkGhostsColision(pacmanX, pacmanY);
}

void MapController::updatePacman() {
  pacman->move(userKey);
  pacman->updatePosition();
  pacmanX = pacman->getPositionX();
  pacmanY = pacman->getPositionY();
  pacmanCh = pacman->getPacmanCh();

  if (points[pacmanX][pacmanY] == -1) {
    score++;
  }
  points[pacmanX][pacmanY] = 1;
}

bool MapController::checkGhostsColision(int x, int y) {
  for (int i = 0; i < ghostsCurrPos.size(); i++) {
    if (ghostsCurrPos[i].first == x &&
        ghostsCurrPos[i].second == y) { // Colision with another ghost
      return true;
    } else if (ghostsCurrPos[i].first == pacmanX &&
               ghostsCurrPos[i].second == pacmanY) { // Colision with pacman
      gameRunning = false;
    }
  }

  return false;
}

bool MapController::canMove(int x, int y) {
  return !map->isWall(y, x) && !checkGhostsColision(x, y);
}

void MapController::updateGPosition(int id) {


  int x = ghostsCurrPos[id].first;
  int y = ghostsCurrPos[id].second;

  bool moved = false;

  while (!moved) {
    int randNumber = rand() % 100;
    if (randNumber >= 0 && randNumber < 25) { // Move UP
      if (canMove(x, y - 1)) {
        y -= 1;
        moved = true;
      }
    } else if (randNumber >= 25 && randNumber < 50) { // Move DOWN
      if (canMove(x, y + 1)) {
        y += 1;
        moved = true;
      }
    } else if (randNumber >= 50 && randNumber < 75) { // Move RIGHT
      if (canMove(x + 1, y)) {
        x += 1;
        moved = true;
      }
    } else {                         // Move LEFT
      if (canMove(x - 1, y)) {
        x -= 1;
        moved = true;
      }
    }
  }

  sem_wait(&ghostMutex);

  ghostsPosition[x][y] = 1;
  ghostsCurrPos[id].first = x;
  ghostsCurrPos[id].second = y;

  sem_post(&ghostMutex);
}

void MapController::updateGhosts() {
  memset(ghostsPosition, 0, sizeof ghostsPosition);

  std::thread ghost1(&MapController::updateGPosition, this, 0);
  std::thread ghost2(&MapController::updateGPosition, this, 1);
  std::thread ghost3(&MapController::updateGPosition, this, 2);
  std::thread ghost4(&MapController::updateGPosition, this, 3);

  ghost1.detach();
  ghost2.detach();
  ghost3.detach();
  ghost4.detach();
}

void MapController::showEndGame() {
  wattron(gameWin, A_BOLD);
  if (score == 431)
    mvwprintw(gameWin, 3, xMax / 2 - 6, " Voce ganhou! ");
  else
    mvwprintw(gameWin, 3, xMax / 2 - 6, " Voce perdeu! ");

  mvwprintw(gameWin, yMax - 5, xMax / 2 - 6, " Fim de Jogo! ");
  mvwprintw(gameWin, yMax - 4, xMax / 2 - 10, " Seu score final:{%d} ", score);
  wattroff(gameWin, A_BOLD);

  wattron(gameWin, A_DIM);
  mvwprintw(gameWin, yMax - 2, xMax / 2 - 20,
            " Aperte a tecla ENTER para voltar ao menu. ");
  wattroff(gameWin, A_DIM);
}

void MapController::run() {
  const auto wait_duration = std::chrono::milliseconds(frameSpeed);
  while (gameRunning) {
    generate();
    updateGhosts();
    updatePacman();
    showScore();

    if (score == 431 || isPacDead()) // Max points ou pac morreu.
      gameRunning = false;
    std::this_thread::sleep_for(wait_duration);
    wrefresh(gameWin);
  }

  generate(); // Show the last frame of the map state
  MapController::showEndGame();
  wrefresh(gameWin);
}
