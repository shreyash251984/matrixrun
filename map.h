

#ifndef MAP_H
#define MAP_H

#define ROWS 10
#define COLS 10

typedef struct
{
    int row;
    int col;
} Position;

void createMap(char map[ROWS][COLS]);

Position generateRandomPosition(char map[ROWS][COLS]);

void initializeSpawns(char map[ROWS][COLS],
                      Position *player,
                      Position *destination,
                      Position *enemy);

void printMap(char map[ROWS][COLS]);

#endif