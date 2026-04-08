#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

extern "C" {
    #include "map.h"
    #include "player.h"
    #include "DAA.h"
}

#define CELL_SIZE 50

int main()
{
    srand(time(NULL));

    char map[ROWS][COLS];
    Position player, destination, enemy;
    Position path[ROWS * COLS];

    do {
        createMap(map);
        initializeSpawns(map, &player, &destination, &enemy);
    } while (!bfsSoundWave(map, player, destination));

    InitWindow(COLS * CELL_SIZE, ROWS * CELL_SIZE, "MatrixRun");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        bool moved = false;

        // 🎮 INPUT (ONLY triggers logic when pressed)
        if (IsKeyPressed(KEY_W)) { movePlayer(map, &player, 'W'); moved = true; }
        if (IsKeyPressed(KEY_S)) { movePlayer(map, &player, 'S'); moved = true; }
        if (IsKeyPressed(KEY_A)) { movePlayer(map, &player, 'A'); moved = true; }
        if (IsKeyPressed(KEY_D)) { movePlayer(map, &player, 'D'); moved = true; }

        // 🤖 ENEMY MOVES ONLY WHEN PLAYER MOVES (IMPORTANT FIX)
        if (moved)
        {
            if (bfsSoundWave(map, player, enemy))
            {
                int pathLength = dijkstraPath(map, enemy, player, path);

                if (pathLength > 1)
                {
                    // clear old enemy
                    map[enemy.row][enemy.col] = '.';

                    enemy = path[1];

                    map[enemy.row][enemy.col] = 'E';
                }
            }
        }

        // 🎨 DRAW (ONLY DISPLAY — no logic here)
        BeginDrawing();
        ClearBackground(RAYWHITE);

        for(int i = 0; i < ROWS; i++)
        {
            for(int j = 0; j < COLS; j++)
            {
                int x = j * CELL_SIZE;
                int y = i * CELL_SIZE;

                Color color;

                if(map[i][j] == 'P') color = GREEN;
                else if(map[i][j] == 'E') color = RED;
                else if(map[i][j] == 'D') color = BLUE;
                else if(map[i][j] == '#') color = BLACK;
                else color = LIGHTGRAY;

                DrawRectangle(x, y, CELL_SIZE - 2, CELL_SIZE - 2, color);
            }
        }

        // 🏁 WIN / LOSE
        if (checkWin(player, destination))
            DrawText("YOU WIN!", 150, 200, 30, GREEN);
            
        if (checkLose(player, enemy))
            DrawText("GAME OVER!", 130, 200, 30, RED);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}