#include<stdio.h>
#include<stdlib.h>
#include <time.h>

#include"map.h"

// MAP INITIALISATION
void createMap(char map[ROWS][COLS])
{
    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLS; j++)
        {
            if(rand() % 5 == 0)
                map[i][j] = '#';   // wall
            else
                map[i][j] = '.';   // path
        }
    }
}


//RANDOM POSITION GENERATOR 

Position generateRandomPosition(char map[ROWS][COLS]) 
{
    Position pos;

    while(1) 
    {
        int r = rand() % ROWS;
        int c = rand() % COLS;

        if(map[r][c] == '.')   // IF THERE IS PATH AND NOT WALL
        {
            pos.row = r;
            pos.col = c;
            return pos;
        }
    }
}

//SPAWN INITIALIZATION


void initializeSpawns(char map[ROWS][COLS], 
                      Position *player, 
                      Position *destination,
                    Position *enemy) 
{
    // PLAYER SPAWN
    *player = generateRandomPosition(map);

    // DESTINATION SPAWN 
    do 
    { 
        //THIS DO WHILE CHECKS IF D AND P ARE AT THE SAME CO ORDINATES OR NO
        *destination = generateRandomPosition(map);
    } 
    while(destination->row == player->row &&
          destination->col == player->col);

    // Enemy spawn (must not overlap player or destination)
    do
    {
        *enemy = generateRandomPosition(map);
    }
    
    while ((enemy->row == player->row &&
            enemy->col == player->col) ||
           (enemy->row == destination->row &&
            enemy->col == destination->col));

    // Mark on map
    map[player->row][player->col] = 'P';
    map[destination->row][destination->col] = 'D';
    map[enemy->row][enemy->col] = 'E';
}
    

//PRINT MAP

void printMap(char map[ROWS][COLS])
{
    printf("\n");

    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLS; j++)
        {
            if(map[i][j] == 'P')
                printf("\033[1;32mP\033[0m ");   // 🟢 Player

            else if(map[i][j] == 'E')
                printf("\033[1;31mE\033[0m ");   // 🔴 Enemy

            else if(map[i][j] == 'D')
                printf("\033[1;34mD\033[0m ");   // 🔵 Destination

            else if(map[i][j] == '#')
                printf("\033[1;37m#\033[0m ");   // ⚪ Wall

            else
                printf(". ");                    // Path
        }
        printf("\n");
    }
}