#include "headers/index.h"

/*
    Notas importantes:
        Ver o video na playlist sobre quando e pq dar refresh/wrefresh.
        Use o getch() como uma forma de pausar a execução do programa. Talvez a
   lógica esteja certa e vc apenas não consegue ver.
*/

int main(void) {
  Game *game = new Game(); // Classe de teste.
  game->init();
  game->run();

  /*
      Get char para esperar user input para sair do programa..
      Tirar no projeto final para sair instantaneamente.
  */
  endwin(); // Finaliza a janela
  delete game;
  
  return 0;
}
