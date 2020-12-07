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
  std::vector<std::pair<int, int> > ghostsCurrPos;
  int ghostsPosition[66][22];
  sem_t ghostMutex;

  // Points
  int points[66][22];
  int score;

public:
  Map();
  Map(WINDOW *win, int yWin, int xWin, unsigned int _frameSpeed);
  ~Map();

  bool isWallH(int x, int y);
  bool isWallX(int x, int y);
  bool isWall(int x, int y);
  bool isEmpty(int x, int y);
  bool isDot(int x, int y);
  bool isStar(int x, int y);
  bool isGhost(int x, int y);

  void generate();
  void configure();
  void updatePacman();
  bool checkGhostsColision(int x, int y);
  void updateGPosition(int id);
  void updateGhosts();
  void readUserKey();
  void run();
};

#endif
