#include "../headers/index.h"
#include "../headers/indexbase.h"

Game::Game() {}

Game::~Game() {
  delete menu;
  delete map;
}

// Método de inicialização.
void Game::init() {
  initscr();                    // Inicia o ncurses.
  getmaxyx(stdscr, yMax, xMax); // Pega dimensões da janela do terminal.
  cbreak();                     // crtl + c to exit.
  noecho();                     // Disable echo on the window.

  // Cria janela, menu e habilita input pelas setinhas.
  gameWin = newwin(yMax, xMax, 0, 0);
  keypad(gameWin, true); // arrow keys input;
  menu = new Menu(gameWin, yMax, xMax);
  map = new Map(gameWin, yMax, xMax, 200);

  // Cria caixa com a borda e atualiza a tela.
  box(gameWin, 0, 0);
  refresh();
  wrefresh(gameWin);
}

void Game::run() {
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

  /*
  Limpa a tela para poder desenhar o mapa.
  Ver drawTitle em Menu.cpp como referência.
  */
  werase(gameWin);
  box(gameWin, 0, 0);
  wrefresh(gameWin);

  // Display dificuldade.
  std::string diff[3] = {"Easy", "Medium", "Hard"};
  mvwprintw(gameWin, 0, 1, "Dificuldade:{%s}", diff[difficulty].c_str());
  wrefresh(gameWin);

  // Lógica do jogo aqui.
  std::thread update_thread(&Map::run, map);
  while (gameRunning) {
    map->readUserKey();
  }
  update_thread.join();
  //
}