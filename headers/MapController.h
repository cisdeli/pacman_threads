#ifndef MAPCONTROLLER_H
#define MAPCONTROLLER_H

#include "index.h"
#include "indexbase.h"

class MapController {
private:
  // MapController config
  WINDOW *gameWin;
  Map *map;
  int yMax, xMax;
  int mapX;
  int mapY;

  unsigned int frameSpeed;
  bool gameRunning;

  void print(int c, int y, int x);
  void printPac(int c, int y, int x);
  void showScore();

  // Pacman
  Pacman *pacman;
  int pacmanX;
  int pacmanY;
  int userKey;
  char pacmanCh = '<';

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
  bool canMove(int x, int y);
  void updateGPosition(int id);
  void updateGhosts();
  void readUserKey();
  void run();
};

#endif
