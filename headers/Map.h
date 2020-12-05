#ifndef MAP_H
#define MAP_H
#include <ncurses.h>
#include <string>
#include <vector>

class Map {
private:
  // Map config
  WINDOW *gameWin;
  int yMax, xMax;
  int mapX = 66, mapY = 22;

  unsigned int frameSpeed;
  bool running;

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

  int isWallH(int x, int y);
  int isWallX(int x, int y);
  int isWall(int x, int y);
  int isEmpty(int x, int y);
  int isDot(int x, int y);
  int isStar(int x, int y);
  void print(int c, int y, int x);

  // Pacman
  int pacmanX;
  int pacmanY;
  int userKey;

  // Ghosts
  int ghostsPosition[66][22];

  // Points
  int points[66][22];

public:
  Map(WINDOW *win, int yWin, int xWin, unsigned int _frameSpeed);
  void generate();
  void configure();
  void updatePacman();
  void updateGhosts();
  void readUserKey();
  void run();
};

#endif
