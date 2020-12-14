#include "headers/index.h"

int main(void) {
  Game *game = new Game(); // Classe principal.
  game->run();

  endwin(); // Finaliza a janela
  delete game;
  return 0;
}
