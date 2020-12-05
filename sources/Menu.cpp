#include "../headers/index.h"
#include "../headers/indexbase.h"

Menu::Menu(WINDOW *win, int yWin, int xWin) {
  // Passa as dimensões e a janela para desenhar nela.
  gameWin = win;
  yMax = yWin;
  xMax = xWin;
}

void Menu::drawTitle() {
  std::vector<std::string> pac_ascii = {
      " _ __   __ _  ___ _ __ ___   __ _ _ __  ",
      "| '_ \\ / _` |/ __| '_ ` _ \\ / _` | '_ \\ ",
      "| |_) | (_| | (__| | | | | | (_| | | | |",
      "| .__/ \\__,_|\\___|_| |_| |_|\\__,_|_| |_|",
      "|_|                                     ",
  };
  std::vector<std::string> pso = {
      " _______  _______  _______ _________ _______ _________ _______         "
      "_______  _______ ",
      "(  ____ )(  ____ )(  ___  )\\__    _/(  ____ \\\\__   __/(  ___  )      "
      " (  ____ \\(  ___  )",
      "| (    )|| (    )|| (   ) |   )  (  | (    \\/   ) (   | (   ) |       "
      "| (    \\/| (   ) |",
      "| (____)|| (____)|| |   | |   |  |  | (__       | |   | |   | | _____ | "
      "(_____ | |   | |",
      "|  _____)|     __)| |   | |   |  |  |  __)      | |   | |   | "
      "|(_____)(_____  )| |   | |",
      "| (      | (\\ (   | |   | |   |  |  | (         | |   | |   | |        "
      "     ) || |   | |",
      "| )      | ) \\ \\__| (___) ||\\_)  )  | (____/\\   | |   | (___) |     "
      "  /\\____) || (___) |",
      "|/       |/   \\__/(_______)(____/   (_______/   )_(   (_______)       "
      "\\_______)(_______)",
  };
  // Looping para printar linha por linha.
  for (unsigned int i = 0; i < pac_ascii.size(); i++)
    mvwaddstr(gameWin, i + 2, (xMax / 3) + 5, pac_ascii[i].c_str());
  for (unsigned int i = 0; i < pso.size(); i++)
    mvwaddstr(gameWin, i + 8, (xMax / 5) + 1, pso[i].c_str());
}

int Menu::userOptions() {
  std::string choices[3] = {"Play", "Difficulty", "Quit"};
  int choice, selected = 0;
  // Menu
  while (1) {
    for (int i = 0; i < 3; i++) {
      if (i == selected)
        wattron(gameWin, A_REVERSE); // Seleciona o texto.
      mvwprintw(gameWin, i + 23, (xMax / 3 + 25) - choices[i].length() / 2,
                choices[i].c_str());
      wattroff(gameWin, A_REVERSE); // Tira o efeito de seleção.
    }
    choice = wgetch(gameWin); // Pega o input do usuario.

    // Setinhas selecionam a opção e coloca limites.
    switch (choice) {
    case KEY_UP:
      selected--;
      if (selected == -1)
        selected = 0;
      break;
    case KEY_DOWN:
      selected++;
      if (selected == 3)
        selected = 2;
      break;
    default:
      break;
    }

    if (choice == 10) // Check enter key
      break;
  }

  // printw("Choice: %s", choices[selected].c_str());
  // Retorna a opcao do usuario para ser tradada na classe game.
  return selected; // 0 = Play, 1 = Difficulty, 2 = quit;
}

int Menu::drawDiff() {
  // Apaga as opcoes iniciais e mantem o titulo.
  werase(gameWin);
  box(gameWin, 0, 0);
  Menu::drawTitle();
  //

  // Mesma lógica da classe drawTitle();.
  std::string choices[3] = {"Easy", "Medium", "Hard"};
  int choice, selected = 0;
  while (1) {
    for (int i = 0; i < 3; i++) {
      if (i == selected)
        wattron(gameWin, A_REVERSE);
      mvwprintw(gameWin, i + 23, (xMax / 3 + 25) - choices[i].length() / 2,
                choices[i].c_str());
      wattroff(gameWin, A_REVERSE);
    }
    choice = wgetch(gameWin);

    switch (choice) {
    case KEY_UP:
      selected--;
      if (selected == -1)
        selected = 0;
      break;
    case KEY_DOWN:
      selected++;
      if (selected == 3)
        selected = 2;
      break;
    default:
      break;
    }

    if (choice == 10) // Check enter key
      break;
  }
  // printw("Choice: %s", choices[selected].c_str());
  return selected; // 0 = easy, 1 = medium, 2 = hard;
}