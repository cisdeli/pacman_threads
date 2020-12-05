#ifndef GHOST_H
#define GHOST_H

#include <utility>

class Ghost {
private:
  int px, py;

public:
  Ghost(int x, int y);
  std::pair<int, int> getPos();
};

#endif
