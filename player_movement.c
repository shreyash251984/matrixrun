#include <stdio.h>
#include "map.h"
#include "player.h"


void movePlayer(char map[ROWS][COLS], Position *player, char move)
{
    int newRow = player->row;
    int newCol = player->col;

    if(move == 'W' || move == 'w')
        newRow--;
    else if(move == 'S' || move == 's')
        newRow++;
    else if(move == 'A' || move == 'a')
        newCol--;
    else if(move == 'D' || move == 'd')
        newCol++;

    if(newRow < 0 || newRow >= ROWS || newCol < 0 || newCol >= COLS)
    {
        printf("Out of bounds!\n");
        return;
    }


    if(map[newRow][newCol] == '#')
    {
        printf("Hit wall!\n");
        return;
    }

    map[player->row][player->col] = '.';


    player->row = newRow;
    player->col = newCol;


    map[player->row][player->col] = 'P';
}


int checkWin(Position player, Position destination)
{
    return (player.row == destination.row &&
            player.col == destination.col);
}


int checkLose(Position player, Position enemy)
{
    return (player.row == enemy.row &&
            player.col == enemy.col);
}