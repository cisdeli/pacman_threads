#include "../headers/index.h"
#include "../headers/indexbase.h"

Ghost::Ghost(int x, int y) {
  px = x;
  py = y;
}

Ghost::~Ghost(){}

std::pair<int, int> Ghost::getPosition() { return std::pair<int, int>{px, py}; }
