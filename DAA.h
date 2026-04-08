#ifndef DAA_H
#define DAA_H

#include "map.h"


int bfsSoundWave(char map[ROWS][COLS], Position start, Position target);

int dijkstraPath(char map[ROWS][COLS],
                 Position start,
                 Position target,
                 Position path[]);

#endif