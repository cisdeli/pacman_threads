#ifndef MENU_H
#define MENU_H

#include "index.h"
#include "indexbase.h"

class Menu {
private:
  WINDOW *gameWin;
  int yMax, xMax;

public:
  Menu(WINDOW *win, int yWin, int xWin);
  void drawTitle();
  int userOptions();
  void drawHelp();
};
#endif
