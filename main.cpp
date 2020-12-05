#include "headers/Ghost.h"
#include "headers/Map.h"
#include "headers/Menu.h"
#include "headers/Game.h"
#include <chrono>
#include <iostream>
#include <ncurses.h>
#include <stdio.h>
#include <string.h>
#include <thread>
#include <utility>

/*
    Notas importantes:
        Ver o video na playlist sobre quando e pq dar refresh/wrefresh.
        Use o getch() como uma forma de pausar a execução do programa. Talvez a
   lógica esteja certa e vc apenas não consegue ver.
*/

int main(void) {
  Game g; // Classe de teste.
  g.init();
  g.run();

  /*
      Get char para esperar user input para sair do programa..
      Tirar no projeto final para sair instantaneamente.
  */
  endwin(); // Finaliza a janela
  return 0;
}
