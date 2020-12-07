#ifndef PACMAN_H
#define PACMAN_H

#include "index.h"
#include "indexbase.h"

class Pacman {
private:
  int x;
  int y;
  char pacmanCh;

  Map *map;

public:
  Pacman(int _x, int _y);
  ~Pacman();
  std::pair<int, int> updatePosition(int userKey);

  int getPositionX() { return x; }
  int getPositionY() { return y; }
  char getPacmanCh() { return pacmanCh; }
};

#endif