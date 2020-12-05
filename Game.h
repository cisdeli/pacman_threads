#ifndef GAME_H
#define GAME_H
#include "Ghost.h"
#include "Map.h"
#include "Menu.h"
#include <ncurses.h>

class Game {
  int yMax, xMax;  // Tamanho maximo da janela.
  WINDOW *gameWin; // Ponteiro para a janela.
  Menu *menu;      // Menu.
  Map *map;

  bool gameRunning; // Variável para verificar o status do jogo.
public:
  void init();
  void run();
};
#endif
