#ifndef GAME_H
#define GAME_H

#include "index.h"
#include "indexbase.h"

class Game {
private:
  int yMax, xMax;  // Tamanho maximo da janela.
  WINDOW *gameWin; // Ponteiro para a janela.
  Menu *menu;      // Menu.
  MapController *map;

  bool gameRunning; // Variável para verificar o status do jogo.
public:
  Game();
  ~Game();

  void init();
  void run();
  void clearScr();
  bool getGameRunning() { return gameRunning; }
  void setGameRunning(bool _gameRunning) { gameRunning = _gameRunning; }
};
#endif
