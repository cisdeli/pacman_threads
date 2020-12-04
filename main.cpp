#include "Ghost.h"
#include "Map.h"
#include "Menu.h"
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

class Game {
  int yMax, xMax;  // Tamanho maximo da janela.
  WINDOW *gameWin; // Ponteiro para a janela.
  Menu *menu; // Menu.

  bool gameRunning = false; // Variável para verificar o status do jogo.

public:
  // Método de inicialização.
  void init() {
    initscr();                    // Inicia o ncurses.
    getmaxyx(stdscr, yMax, xMax); // Pega dimensões da janela do terminal.
    cbreak();                     // crtl + c to exit.
    noecho();                     // Disable echo on the window.

    // Cria janela, menu e habilita input pelas setinhas.
    gameWin = newwin(yMax, xMax, 0, 0);
    keypad(gameWin, true); // arrow keys input;
    menu = new Menu(gameWin, yMax, xMax);

    // Cria caixa com a borda e atualiza a tela.
    box(gameWin, 0, 0);
    refresh();
    wrefresh(gameWin);
  }

  void run() {
    menu->drawTitle();
    int op = menu->userOptions();
    int difficulty = 0; // Dificuldate padrao: facil;
    while (!gameRunning) {
      if (op == 2)
        return; // Usuário selecionou quit.
      else if (op == 1) {
        difficulty = menu->drawDiff(); // Usuário selecionou Difficulty.
        op = menu->userOptions();
      } else if (op == 0)
        gameRunning = true; // Usuário selecionou Play.
    }

    while (gameRunning) {
      /*
          Limpa a tela para poder desenhar o mapa.
          Ver drawTitle em Menu.cpp como referência.
      */
      werase(gameWin);
      box(gameWin, 0, 0);
      wrefresh(gameWin);

      // Lógica do jogo aqui?
      mvwprintw(gameWin, 10, 10, "Jogo aqui hehe");
      std::string diff[3] = {"Easy", "Medium", "Hard"};
      mvwprintw(gameWin, 11, 10, "Dificuldade: %s", diff[difficulty].c_str());
      wrefresh(gameWin);
      //
      getch();
      break;
    }
  }
};

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
