#include "headers/index.h"

int main(void) {
  Game *game = new Game(); // Classe de teste.
  game->run();

  endwin(); // Finaliza a janela
  delete game;
  return 0;
}
