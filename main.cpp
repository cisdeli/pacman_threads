#include "headers/index.h"

/*
    Notas importantes:
        Ver o video na playlist sobre quando e pq dar refresh/wrefresh.
        Use o getch() como uma forma de pausar a execução do programa. Talvez a
   lógica esteja certa e vc apenas não consegue ver.
*/

int main(void) {
  Game *game = new Game(); // Classe de teste.
  game->run();

  endwin(); // Finaliza a janela
  delete game;

  return 0;
}
