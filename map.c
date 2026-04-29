#include <stdio.h>
#include <stdlib.h>

#include "map.h"

// ================= CREATE MAP =================
void createMap(char map[ROWS][COLS])
{
    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLS; j++)
        {
            // 🔲 BORDER WALLS
            if (i == 0 || j == 0 || i == ROWS-1 || j == COLS-1)
            {
                map[i][j] = '#';
            }
            // 🔥 SMART WALL GENERATION (cluster + density)
            else if ((rand() % 3 == 0) ||
                     (i > 0 && map[i-1][j] == '#') ||
                     (j > 0 && map[i][j-1] == '#'))
            {
                map[i][j] = '#';
            }
            // EMPTY SPACE
            else
            {
                map[i][j] = '.';
            }
        }
    }
}

// ================= RANDOM POSITION =================
Position generateRandomPosition(char map[ROWS][COLS])
{
    Position pos;

    // try limited times (avoid infinite loop)
    for(int tries = 0; tries < 1000; tries++)
    {
        int r = rand() % ROWS;
        int c = rand() % COLS;

        if(map[r][c] == '.')
        {
            pos.row = r;
            pos.col = c;
            return pos;
        }
    }

    // fallback (safe position)
    pos.row = 1;
    pos.col = 1;
    return pos;
}

// ================= SPAWN INITIALIZATION =================
void initializeSpawns(char map[ROWS][COLS],
                      Position *player,
                      Position *destination,
                      Position *enemy)
{
    // Player
    *player = generateRandomPosition(map);

    // Destination (not same as player)
    do
    {
        *destination = generateRandomPosition(map);
    }
    while(destination->row == player->row &&
          destination->col == player->col);

    // Enemy (not same as player or destination)
    do
    {
        *enemy = generateRandomPosition(map);
    }
    while ((enemy->row == player->row &&
            enemy->col == player->col) ||
           (enemy->row == destination->row &&
            enemy->col == destination->col));

    // Place on map
    map[player->row][player->col] = 'P';
    map[destination->row][destination->col] = 'D';
    map[enemy->row][enemy->col] = 'E';
}

void printMap(char map[ROWS][COLS])
{
    printf("\n");

    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLS; j++)
        {
            if(map[i][j] == 'P')
                printf("\033[1;32mP\033[0m ");

            else if(map[i][j] == 'E')
                printf("\033[1;31mE\033[0m ");

            else if(map[i][j] == 'D')
                printf("\033[1;34mD\033[0m ");

            else if(map[i][j] == '#')
                printf("\033[1;37m#\033[0m ");

            else
                printf(". ");
        }
        printf("\n");
    }
}