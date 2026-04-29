#ifndef PLAYER_H
#define PLAYER_H

#include "map.h"

void movePlayer(char map[ROWS][COLS], Position *player, char move);

int checkWin(Position player, Position destination);

int checkLose(Position player, Position enemy);

#endif