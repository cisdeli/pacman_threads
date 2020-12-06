#ifndef MAP_H
#define MAP_H

#include "index.h"
#include "indexbase.h"

class Map {
private:
  // Map config
  WINDOW *gameWin;
  int yMax, xMax;
  int mapX = 66, mapY = 22;

  unsigned int frameSpeed;
  bool gameRunning;

  char map[22][66] = {
      "#################################################################",
      "##x...........................x###x...........................x##",
      "##x.x#######x.x#############x.x###x.x#############x.x#######x.x##",
      "##x*x#######x.x#############x.x###x.x#############x.x#######x*x##",
      "##x...........................................................x##",
      "##x.x#######x.x###x.x#######################x.x###x.x#######x.x##",
      "##x.x#######x.x###x...........x###x...........x###x.x#######x.x##",
      "##x...........x#############x.x###x.x#############x...........x##",
      "############x.x#############x.x###x.x#############x.x############",
      "############x.x###x...........................x###x.x############",
      "############x.x###x.x#######################x.x###x.x############",
      "############x.x###x.x#######         #######x.x###x.x############",
      "############x.x###x.x#######         #######x.x###x.x############",
      "##x.................x#######         #######x.................x##",
      "##x.x#######x.x###x.x#######################x.x###x.x#######x.x##",
      "##x*....x###x.......................................x###x....*x##",
      "######x.x###x.x###x.x#######################x.x###x.x###x.x######",
      "##x...........x###x...........x###x...........x###x...........x##",
      "##x.x#######################x.x###x.x#######################x.x##",
      "##x.x#######################x.x###x.x#######################x.x##",
      "##x...........................................................x##",
      "#################################################################"};

  void print(int c, int y, int x);
  void printPac(int c, int y, int x);

  void showScore();

  // Pacman
  int pacmanX;
  int pacmanY;
  int userKey;
  char pacmanCh;

  // Ghosts
  Ghost *ghost1;
  Ghost *ghost2;
  int ghostsPosition[66][22];

  // Points
  int points[66][22];
  int score;

public:
  Map();
  Map(WINDOW *win, int yWin, int xWin, unsigned int _frameSpeed);
  ~Map();

  int isWallH(int x, int y);
  int isWallX(int x, int y);
  int isWall(int x, int y);
  int isEmpty(int x, int y);
  int isDot(int x, int y);
  int isStar(int x, int y);
  int isGhost(int x, int y);

  void generate();
  void configure();
  void updatePacman();
  void updateGhosts();
  void readUserKey();
  void run();
};

#endif
