#ifndef GHOST_H
#define GHOST_H

#include "index.h"
#include "indexbase.h"

class Ghost {
private:
  int x, y;
  int maxX, maxY;
  Map *map;

public:
  Ghost(int x, int y, int maxX, int maxY);
  ~Ghost();

  std::pair<int, int> getPosition();
  void updatePosition();
};

#endif
