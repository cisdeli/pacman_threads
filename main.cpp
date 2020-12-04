#include "Ghost.h"
#include "Map.h"
#include "Menu.h"
#include <chrono>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <thread>
#include <utility>

int main(void) {
  Ghost g(7, 8);
  std::pair<int, int> posG = g.getPos();
  printf("Ghost: %d %d\n", posG.first, posG.second);

  return 0;
}
