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

Map::~Map() {
   delete ghost1; 
   delete ghost2;
}

int Map::isWallH(int x, int y) { return map[x][y] == '#' ? 1 : 0; }
int Map::isWallX(int x, int y) { return map[x][y] == 'x' ? 1 : 0; }
int Map::isEmpty(int x, int y) { return map[x][y] == ' ' ? 1 : 0; }
int Map::isDot(int x, int y) { return map[x][y] == '.' ? 1 : 0; }
int Map::isStar(int x, int y) { return map[x][y] == '*' ? 1 : 0; }
int Map::isWall(int x, int y) { return Map::isWallH(x, y) || Map::isWallX(x, y); }
int Map::isGhost(int x, int y) { return map[x][y] == '$'; }

void Map::print(int c, int y, int x) {
  start_color();
  init_pair(1, COLOR_GREEN, COLOR_GREEN);
  wattron(gameWin, A_BOLD);
  wattron(gameWin, COLOR_PAIR(1));
  mvwaddch(gameWin, y, x, c);
  wattroff(gameWin, COLOR_PAIR(1));
  wattroff(gameWin, A_BOLD);
}

void Map::configure() {
  gameRunning = true;
  pacmanX = 3;
  pacmanY = 1;

  memset(points, -1, sizeof points);
  points[pacmanX][pacmanY] = 1;

  /// Configure Ghosts here... ///

  ghost1 = new Ghost(10, 4, mapX, mapY);
  ghost2 = new Ghost(61, 3, mapX, mapY);

  memset(ghostsPosition, -1, sizeof ghostsPosition);
  ghostsPosition[10][4]   = 1;
  ghostsPosition[3][61]  = 1;
}

void Map::generate() {
  for (int i = 0; i < mapX; i++)
    for (int j = 0; j < mapY; j++) {
      if (j == pacmanY && i == pacmanX)
        mvwaddch(gameWin, j + 8, i + xMax / 3 - 8, (int)'@');

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
      else if (Map::isStar(j, i))
        if (points[i][j] == 1)
          mvwaddch(gameWin, j + 8, i + xMax / 3 - 8, (int)' ');
        else
          mvwaddch(gameWin, j + 8, i + xMax / 3 - 8, (int)'.');
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
      points[pacmanX][pacmanY] = 1;
    }
    break;
  case KEY_DOWN:
    if (!isWall(pacmanY + 1 % mapY, pacmanX)) {
      pacmanY += 1 % mapY;
      points[pacmanX][pacmanY] = 1;
    }
    break;
  case KEY_RIGHT:
    if (!isWall(pacmanY, pacmanX + 1 % mapX)) {
      pacmanX += 1 % mapX;
      points[pacmanX][pacmanY] = 1;
    }
    break;
  case KEY_LEFT:
    if (!isWall(pacmanY, pacmanX - 1 % mapX)) {
      pacmanX -= 1 % mapX;
      points[pacmanX][pacmanY] = 1;
    }
    break;
  }
}

void Map::updateGhosts() {
  std::thread moveGhost1(&Ghost::updatePosition, ghost1);
  std::thread moveGhost2(&Ghost::updatePosition, ghost2);

  std::pair<int, int> ghostPos1 = ghost1->getPosition();
  std::pair<int, int> ghostPos2 = ghost2->getPosition();

  memset(ghostsPosition, -1, sizeof ghostsPosition);
  ghostsPosition[ghostPos1.first][ghostPos1.second] = 1;
  ghostsPosition[ghostPos2.first][ghostPos2.second] = 1;

  moveGhost1.join();
  moveGhost2.join();
}

void Map::run() {
  const auto wait_duration = std::chrono::milliseconds(frameSpeed);
  while (gameRunning) {
    generate();
    updateGhosts();
    updatePacman();

    std::this_thread::sleep_for(wait_duration);
    wrefresh(gameWin);
  }
}
