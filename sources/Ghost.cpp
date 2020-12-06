#include "../headers/index.h"
#include "../headers/indexbase.h"

Ghost::Ghost(int _x, int _y, int _maxX, int _maxY) {
  x = _x;
  y = _y;
  maxX = _maxX;
  maxY = _maxY;
  map = new Map();
}

Ghost::~Ghost(){
  delete map;
}

std::pair<int, int> Ghost::getPosition() { return std::pair<int, int>{x, y}; }

void Ghost::updatePosition() {
  bool moved = false;

  while(!moved) {
    int randNumber = rand()%100;
    if(randNumber >= 0 && randNumber < 25) {
        if (!map->isWall(y - 1 % maxY, x)) {
          y -= 1 % maxY;
          moved = true;
        }
    } else if(randNumber >= 25 && randNumber < 50) {
        if (!map->isWall(y + 1 % maxY, x)) {
          y += 1 % maxY;
          moved = true;
        }
    } else if(randNumber >= 50 && randNumber < 75) {
        if (!map->isWall(y, x + 1 % maxX)) {
          x += 1 % maxX;
          moved = true;
        }
    } else {
        if (!map->isWall(y, x + 1 % maxX)) {
          x -= 1 % maxX;
          moved = true;
        }
    }
  }

  return;
}
