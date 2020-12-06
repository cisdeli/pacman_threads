#include "../headers/index.h"
#include "../headers/indexbase.h"

Map::Map(WINDOW *win, int yWin, int xWin, unsigned int _frameSpeed) {
  // Passa as dimensões e a janela para desenhar nela.
  gameWin = win;
  yMax = yWin;
  xMax = xWin;
  frameSpeed = _frameSpeed;
  Map::configure();
}

Map::~Map() { delete ghostArray; }

int Map::isWallH(int x, int y) { return map[x][y] == '#' ? 1 : 0; }
int Map::isWallX(int x, int y) { return map[x][y] == 'x' ? 1 : 0; }
int Map::isEmpty(int x, int y) { return map[x][y] == ' ' ? 1 : 0; }
int Map::isDot(int x, int y) { return map[x][y] == '.' ? 1 : 0; }
int Map::isStar(int x, int y) { return map[x][y] == '*' ? 1 : 0; }
int Map::isWall(int x, int y) {
  return Map::isWallH(x, y) || Map::isWallX(x, y);
}

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
  score = 0;
  gameRunning = true;
  pacmanX = 3;
  pacmanY = 1;
  pacmanCh = '<';

  memset(points, -1, sizeof points);
  points[pacmanX][pacmanY] = 1;

  /// Configure Ghosts here... ///
  ghostArray = new Ghost(4, 4);
  memset(ghostsPosition, -1, sizeof ghostsPosition);
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

void Map::updateGhosts() {
  /// Implementar quando tiver a classe Ghost
  // for(int i = 0; i < ghostArray.size(); i++) {
  //   int x = ghostArray[i]->getPositionX();
  //   int y = ghostArray[i]->getPositionY();

  //   ghostsPosition[x][y] = 1;
  // }
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
  }
}
