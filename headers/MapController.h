#ifndef MAPCONTROLLER_H
#define MAPCONTROLLER_H

#include "index.h"
#include "indexbase.h"

class MapController {
private:
  // Window config
  WINDOW *gameWin;
  int yMax, xMax;

  // Map config
  Map *map;
  unsigned int frameSpeed;
  bool gameRunning;

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

  // Internal methods
  void print(int c, int y, int x, int cpair);
  void showScore();
  void printLine(int i, int j, char c);

  bool checkGhostsColision(int x, int y);
  bool canMove(int x, int y);
  void configure();
  void updatePacman();
  bool isPacDead();
  void generate();
  void showEndGame();
  void updateGPosition(int id);
  void updateGhosts();

public:
  MapController();
  MapController(WINDOW *win, int yWin, int xWin, unsigned int _frameSpeed);
  ~MapController();

  bool getGameState();
  int readUserKey();
  void run();
};

#endif
