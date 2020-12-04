#ifndef MENU_H
#define MENU_H
#include <ncurses.h>

class Menu {
  WINDOW *gameWin;
  int yMax, xMax;

public:
  Menu(WINDOW *win, int yWin, int xWin);
  void drawTitle();
  int userOptions();
  int drawDiff();
};
#endif
