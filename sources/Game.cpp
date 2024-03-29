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
  map = new MapController(gameWin, yMax, xMax, 200);

  // Cria caixa com a borda e atualiza a tela.
  box(gameWin, 0, 0);
  refresh();
  wrefresh(gameWin);
}

// Método para limpar a tela e redesenhar a caixa.
void Game::clearScr() {
  werase(gameWin);
  box(gameWin, 0, 0);
  wrefresh(gameWin);
}

void Game::run() {
  init();

  menu->drawTitle();
  int op = menu->userOptions();
  while (!gameRunning) {
    if (op == 2)
      return; // Usuário selecionou quit.
    else if (op == 1) {
      menu->drawHelp(); // Usuário selecionou Help.
      op = menu->userOptions();
    } else if (op == 0)
      gameRunning = true; // Usuário selecionou Play.
  }

  // Limpa a tela para poder desenhar o mapa.
  clearScr();
  wrefresh(gameWin);

  // Lógica do jogo aqui.
  std::thread update_thread(&MapController::run,
                            map); // Thread principal para ficar renderizando o
                                  // mapa e atualizando os fantasmas
  int userKey;
  while (gameRunning) {
    gameRunning = map->getGameState();
    userKey = map->readUserKey();
  }
  update_thread.join();
  while (userKey != 10) // Checa pelo enter para reiniciar para o menu
    userKey = wgetch(gameWin);

  clearScr();
  run();
}
