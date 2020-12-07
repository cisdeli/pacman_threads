#include "../headers/index.h"
#include "../headers/indexbase.h"

Map::Map() {}

Map::Map(WINDOW *win, int yWin, int xWin, unsigned int _frameSpeed) {
  // Passa as dimensões e a janela para desenhar nela.
  gameWin = win;
  yMax = yWin;
  xMax = xWin;
  frameSpeed = _frameSpeed;
  Map::configure();
}

Map::~Map() {}

bool Map::getGameState() { return gameRunning; }

bool Map::isWallH(int x, int y) { return map[x][y] == '#'; }
bool Map::isWallX(int x, int y) { return map[x][y] == 'x'; }
bool Map::isEmpty(int x, int y) { return map[x][y] == ' '; }
bool Map::isDot(int x, int y) { return map[x][y] == '.'; }
bool Map::isStar(int x, int y) { return map[x][y] == '*'; }
bool Map::isWall(int x, int y) {
  return Map::isWallH(x, y) || Map::isWallX(x, y);
}
bool Map::isGhost(int x, int y) { return map[x][y] == '$'; }

void Map::print(int c, int y, int x) {
  start_color();
  init_pair(1, COLOR_GREEN, COLOR_GREEN);
  wattron(gameWin, A_BOLD);
  wattron(gameWin, COLOR_PAIR(1));
  mvwaddch(gameWin, y, x, c);
  wattroff(gameWin, COLOR_PAIR(1));
  wattroff(gameWin, A_BOLD);
}

void Map::printPac(int c, int y, int x) {
  start_color();
  init_pair(2, COLOR_YELLOW, COLOR_BLACK);
  wattron(gameWin, A_BOLD);
  wattron(gameWin, COLOR_PAIR(2));
  mvwaddch(gameWin, y, x, c);
  wattroff(gameWin, COLOR_PAIR(2));
  wattroff(gameWin, A_BOLD);
}

void Map::showScore() {
  mvwprintw(gameWin, 0, xMax / 2 + 10, "Score:{%d}", score);
}

void Map::configure() {
  // Configure game
  score = 0;
  gameRunning = true;

  // Configure pacman
  pacmanX = 3;
  pacmanY = 1;
  pacmanCh = '<';

  // Configure points
  memset(points, -1, sizeof points);
  points[pacmanX][pacmanY] = 1;

  /// Configure Ghosts
  memset(ghostsPosition, 0, sizeof ghostsPosition);
  ghostsCurrPos.push_back({10, 4});
  ghostsCurrPos.push_back({61, 3});
  ghostsCurrPos.push_back({10, 20});
  ghostsCurrPos.push_back({30, 15});
  ghostsPosition[4][10] = 1;
  ghostsPosition[3][61] = 1;
  ghostsPosition[20][10] = 1;
  ghostsPosition[15][30] = 1;

  // Semaphore config
  sem_init(&ghostMutex, 0, 1);
}

void Map::generate() {
  for (int i = 0; i < mapX; i++)
    for (int j = 0; j < mapY; j++) {
      if (j == pacmanY && i == pacmanX)
        Map::printPac((int)pacmanCh, j + 8, i + xMax / 3 - 8);

      else if (ghostsPosition[i][j] == 1)
        mvwaddch(gameWin, j + 8, i + xMax / 3 - 8, (int)'$');

      else if (Map::isWallH(j, i))
        Map::print((int)'#', j + 8, i + xMax / 3 - 8);

      else if (Map::isWallX(j, i))
        mvwaddch(gameWin, j + 8, i + xMax / 3 - 8, (int)' ');

      else if (Map::isDot(j, i)) {
        if (points[i][j] == 1)
          mvwaddch(gameWin, j + 8, i + xMax / 3 - 8, (int)' ');
        else
          mvwaddch(gameWin, j + 8, i + xMax / 3 - 8, (int)'.');
      }

      else if (Map::isEmpty(j, i))
        mvwaddch(gameWin, j + 8, i + xMax / 3 - 8, (int)' ');

      // Caso sobre tempo implementar powerup
      else if (Map::isStar(j, i)) {
        if (points[i][j] == 1)
          mvwaddch(gameWin, j + 8, i + xMax / 3 - 8, (int)' ');
        else
          mvwaddch(gameWin, j + 8, i + xMax / 3 - 8, (int)'.');
      }
    }
}

void Map::readUserKey() {
  if (gameRunning)
    userKey = wgetch(gameWin); // Pega o input do usuario.
}

void Map::updatePacman() {
  switch (userKey) {
  case KEY_UP:
    if (!isWall(pacmanY - 1 % mapY, pacmanX)) {
      pacmanY -= 1 % mapY;
      if (points[pacmanX][pacmanY] == -1)
        score++;
      points[pacmanX][pacmanY] = 1;
      pacmanCh = 'v';
    }
    break;
  case KEY_DOWN:
    if (!isWall(pacmanY + 1 % mapY, pacmanX)) {
      pacmanY += 1 % mapY;
      if (points[pacmanX][pacmanY] == -1)
        score++;
      points[pacmanX][pacmanY] = 1;
      pacmanCh = '^';
    }
    break;
  case KEY_RIGHT:
    if (!isWall(pacmanY, pacmanX + 1 % mapX)) {
      pacmanX += 1 % mapX;
      if (points[pacmanX][pacmanY] == -1)
        score++;
      points[pacmanX][pacmanY] = 1;
      pacmanCh = '<';
    }
    break;
  case KEY_LEFT:
    if (!isWall(pacmanY, pacmanX - 1 % mapX)) {
      pacmanX -= 1 % mapX;
      if (points[pacmanX][pacmanY] == -1)
        score++;
      points[pacmanX][pacmanY] = 1;
      pacmanCh = '>';
    }
    break;
  }
}

bool Map::checkGhostsColision(int x, int y) {
  for (int i = 0; i < ghostsCurrPos.size(); i++) {
    if (ghostsCurrPos[i].first == x && ghostsCurrPos[i].second == y) {
      return true;
    }
  }

  return false;
}

void Map::updateGPosition(int id) {
  sem_wait(&ghostMutex);

  int x = ghostsCurrPos[id].first;
  int y = ghostsCurrPos[id].second;

  bool moved = false;

  while (!moved) {
    int randNumber = rand() % 100;
    if (randNumber >= 0 && randNumber < 25) {
      if (!isWall(y - 1 % mapY, x) && !checkGhostsColision(x, y - 1 % mapY)) {
        y -= 1 % mapY;
        moved = true;
      }
    } else if (randNumber >= 25 && randNumber < 50) {
      if (!isWall(y + 1 % mapY, x) && !checkGhostsColision(x, y + 1 % mapY)) {
        y += 1 % mapY;
        moved = true;
      }
    } else if (randNumber >= 50 && randNumber < 75) {
      if (!isWall(y, x + 1 % mapX) && !checkGhostsColision(x + 1 % mapX, y)) {
        x += 1 % mapX;
        moved = true;
      }
    } else {
      if (!isWall(y, x - 1 % mapX) && !checkGhostsColision(x - 1 % mapX, y)) {
        x -= 1 % mapX;
        moved = true;
      }
    }
  }

  ghostsPosition[x][y] = 1;
  ghostsCurrPos[id].first = x;
  ghostsCurrPos[id].second = y;

  sem_post(&ghostMutex);
}

void Map::updateGhosts() {
  memset(ghostsPosition, 0, sizeof ghostsPosition);

  std::thread ghost1(&Map::updateGPosition, this, 0);
  std::thread ghost2(&Map::updateGPosition, this, 1);
  std::thread ghost3(&Map::updateGPosition, this, 2);
  std::thread ghost4(&Map::updateGPosition, this, 3);

  ghost1.join();
  ghost2.join();
  ghost3.join();
  ghost4.join();
}

void Map::showEndGame() {
  wattron(gameWin, A_BOLD);
  if (score == 431)
    mvwprintw(gameWin, 3, xMax / 2 - 6, " Voce ganhou! ");
  else
    mvwprintw(gameWin, 3, xMax / 2 - 6, " Voce perdeu! ");

  mvwprintw(gameWin, yMax - 5, xMax / 2 - 6, " Fim de Jogo! ");
  mvwprintw(gameWin, yMax - 4, xMax / 2 - 10, " Seu score final:{%d} ", score);
  wattroff(gameWin, A_BOLD);

  wattron(gameWin, A_DIM);
  mvwprintw(gameWin, yMax - 2, xMax / 2 - 21,
            " Aperte qualquer tecla para voltar ao menu. ");
  wattroff(gameWin, A_DIM);
}

void Map::run() {
  const auto wait_duration = std::chrono::milliseconds(frameSpeed);
  while (gameRunning) {
    generate();
    updateGhosts();
    updatePacman();
    showScore();

    std::this_thread::sleep_for(wait_duration);
    wrefresh(gameWin);
    if (score == 431) // Max points
      gameRunning = false;
  }
  Map::showEndGame();
  wrefresh(gameWin);
}
