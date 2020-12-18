#include "headers/index.h"

int main(void) {
  Game *game = new Game(); // Classe principal.
  game->run();             // Método principal do jogo

  endwin(); // Finaliza a janela
  delete game;
  return 0;
}
