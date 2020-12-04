#include "Ghost.h"
#include <utility>

Ghost::Ghost(int x, int y) {
  px = x;
  py = y;
}

std::pair<int, int> Ghost::getPos() { return std::pair<int, int>{px, py}; }
