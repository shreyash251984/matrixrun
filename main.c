#include <termios.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "map.h"
#include "player.h"
#include "DAA.h"
#include <unistd.h>

char getch()
{
    struct termios oldt, newt;
    char ch;

    tcgetattr(STDIN_FILENO, &oldt);  
    newt = oldt;

    newt.c_lflag &= ~(ICANON | ECHO);

    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return ch;
}

int main()
{
    srand(time(NULL));

    char map[ROWS][COLS];

    Position player, destination, enemy;
    Position path[ROWS * COLS];

    char move,choice;
    do{

    do
    {
        createMap(map);
        initializeSpawns(map, &player, &destination, &enemy);

    } while (!bfsSoundWave(map, player, destination));

    while (1)
    {
        system("cls");
        printf("        MATRIX RUN GAME\n");
        printf("=================================\n");
        printf("Controls: W A S D\n");
        printf("Reach D | Avoid E\n");
        printf("=================================\n\n");
        printMap(map);

        printf("\nYour Move ➤ ");
        move = getch();
        printf("%c\n", move);


        movePlayer(map, &player, move);


        if (checkWin(player, destination))
        {
            printMap(map);
            printf("\n YOU WIN! Reached Destination!\n");
            break;
        }


        if (bfsSoundWave(map, player, enemy))
        {
            printf("\n Enemy detected you!\n");

            int pathLength = dijkstraPath(map, enemy, player, path);

        
            if (pathLength > 1)
            {
            
                map[enemy.row][enemy.col] = '.';

        
                enemy = path[1];

        
                map[enemy.row][enemy.col] = 'E';
            }
        }

    
        if (checkLose(player, enemy))
        {
            printMap(map);
            printf("\n GAME OVER! Enemy caught you!\n");
            break;
        }
        usleep(120000); 
    }
     printf("\nPlay again? (y/n): ");
        choice = getch(); 

    } while (choice == 'y' || choice == 'Y');
    return 0;
}