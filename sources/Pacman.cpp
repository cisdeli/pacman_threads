#include "../headers/index.h"
#include "../headers/indexbase.h"

Pacman::Pacman(int _x, int _y) {
  x = _x;
  y = _y;
  dir = RIGHT;
  map = new Map();
};

Pacman::~Pacman() { delete map; }

void Pacman::move(int userKey) {
  if (userKey == KEY_UP)
    dir = UP;
  if (userKey == KEY_DOWN)
    dir = DOWN;
  if (userKey == KEY_RIGHT)
    dir = RIGHT;
  if (userKey == KEY_LEFT)
    dir = LEFT;
}

void Pacman::updatePosition() {
  int mapX = map->getMapX();
  int mapY = map->getMapY();
  switch (dir) {
  case UP:
    if (!map->isWall(y - 1 % mapY, x)) {
      y -= 1 % mapY;
      pacmanCh = 'v';
    }
    break;
  case DOWN:
    if (!map->isWall(y + 1 % mapY, x)) {
      y += 1 % mapY;
      pacmanCh = '^';
    }
    break;
  case RIGHT:
    if (!map->isWall(y, x + 1 % mapX)) {
      x += 1 % mapX;
      pacmanCh = '<';
    }
    break;
  case LEFT:
    if (!map->isWall(y, x - 1 % mapX)) {
      x -= 1 % mapX;
      pacmanCh = '>';
    }
    break;
  default:
    pacmanCh = '<';
  }
}
