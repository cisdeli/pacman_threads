#ifndef MAPCONTROLLER_H
#define MAPCONTROLLER_H

#include "index.h"
#include "indexbase.h"

class MapController {
private:
  // MapController config
  WINDOW *gameWin;
  Map *mapObj;
  int yMax, xMax;
  int mapX = 66, mapY = 22;

  unsigned int frameSpeed;
  bool gameRunning;

  

  void print(int c, int y, int x);
  void printPac(int c, int y, int x);

  void showScore();

  // Pacman
  int pacmanX;
  int pacmanY;
  int userKey;
  char pacmanCh;

  // Ghosts
  std::vector<std::pair<int, int>> ghostsCurrPos;
  int ghostsPosition[66][22];
  sem_t ghostMutex;

  // Points
  int points[66][22];
  int score;

public:
  MapController();
  MapController(WINDOW *win, int yWin, int xWin, unsigned int _frameSpeed);
  ~MapController();

  bool isPacDead();
  bool getGameState();

  void showEndGame();

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
