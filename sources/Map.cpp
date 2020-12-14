#include "../headers/index.h"
#include "../headers/indexbase.h"

Map::Map() {}

bool Map::isWallH(int x, int y) { return map[x][y] == '#'; }
bool Map::isWallX(int x, int y) { return map[x][y] == 'x'; }
bool Map::isDot(int x, int y) { return map[x][y] == '.'; }
bool Map::isWall(int x, int y) { return Map::isWallH(x, y) || Map::isWallX(x, y); }
