#ifndef GHOST_H
#define GHOST_H

#include "index.h"
#include "indexbase.h"

class Ghost {
private:
  int px, py;

public:
  Ghost(int x, int y);
  ~Ghost();
  std::pair<int, int> getPosition();
};

#endif
