#include "../headers/index.h"
#include "../headers/indexbase.h"

Pacman::Pacman(int _x, int _y) {
  x = _x;
  y = _y; 

  map = new Map();
};

Pacman::~Pacman() {
  delete map;
}

std::pair<int, int> Pacman::updatePosition(int userKey) {
  int mapX = map->getMapX();
  int mapY = map->getMapY();
  switch (userKey) {
  case KEY_UP:
    if (!map->isWall(y - 1 % mapY, x)) {
      y -= 1 % mapY;
      pacmanCh = 'v';
    }
    break;
  case KEY_DOWN:
    if (!map->isWall(y + 1 % mapY, x)) {
      y += 1 % mapY;
      pacmanCh = '^';
    }
    break;
  case KEY_RIGHT:
    if (!map->isWall(y, x + 1 % mapX)) {
      x += 1 % mapX;
      pacmanCh = '<';
    }
    break;
  case KEY_LEFT:
    if (!map->isWall(y, x - 1 % mapX)) {
      x -= 1 % mapX;
      pacmanCh = '>';
    }
    break;
  default:
    pacmanCh = '<';
  }

  return {x, y};
}