#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

extern "C" {
#include "map.h"
#include "player.h"
#include "DAA.h"
}

#define CELL_SIZE 60
#define TOP_BAR 80

enum GameState { MENU, PLAYING, END };


void resetGame(char map[ROWS][COLS],
Position *player,
Position *destination,
Position *enemy,
int *score,
float *startTime,
bool *gameOver,
bool *gameWin,
bool *timerStarted)
{
    do {
        createMap(map);
        initializeSpawns(map, player, destination, enemy);
    } while (!bfsSoundWave(map, *player, *destination));

    *score = 0;
    *startTime = 0;
    *gameOver = false;
    *gameWin = false;
    *timerStarted = false;
}


int main()
{
    srand(time(NULL));

    char map[ROWS][COLS];
    Position player, destination, enemy;
    Position path[ROWS * COLS];

    GameState gameState = MENU;

    bool gameOver = false;
    bool gameWin = false;
    bool timerStarted = false;

    int score = 0;
    int bestScore = 0;

    int round = 1;
    int maxRounds = 3;

    float startTime = 0;
    float elapsedTime = 0;

    int screenWidth = COLS * CELL_SIZE;
    int screenHeight = ROWS * CELL_SIZE + TOP_BAR;

    InitWindow(screenWidth, screenHeight, "MatrixRun");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();

        // 🌌 Background
        DrawRectangleGradientV(0, 0, screenWidth, screenHeight,
                               Color{30,30,35,255},
                               Color{10,10,15,255});

        // ================= MENU =================
        if (gameState == MENU)
        {
            DrawText("MATRIX RUN", screenWidth/2 - 180, 150, 50, GREEN);
            DrawText("Press ENTER to Start", screenWidth/2 - 170, 250, 24, WHITE);

            if (IsKeyPressed(KEY_ENTER))
            {
                round = 1;
                bestScore = 0;

                resetGame(map, &player, &destination, &enemy,
                          &score, &startTime, &gameOver, &gameWin, &timerStarted);

                gameState = PLAYING;
            }
        }

    
        else if (gameState == PLAYING)
        {
            bool moved = false;
            bool active = !gameOver && !gameWin;

            // INPUT
            if (active)
            {
                if (IsKeyPressed(KEY_W)) { movePlayer(map, &player, 'W'); moved = true; }
                if (IsKeyPressed(KEY_S)) { movePlayer(map, &player, 'S'); moved = true; }
                if (IsKeyPressed(KEY_A)) { movePlayer(map, &player, 'A'); moved = true; }
                if (IsKeyPressed(KEY_D)) { movePlayer(map, &player, 'D'); moved = true; }

                if (moved)
                {
                    score++;

                    if (!timerStarted)
                    {
                        startTime = GetTime();
                        timerStarted = true;
                    }
                }
            }

            
            if (moved && active)
            {
                if (bfsSoundWave(map, player, enemy))
                {
                    int len = dijkstraPath(map, enemy, player, path);

                    if (len > 1)
                    {
                        if (map[enemy.row][enemy.col] != 'D')
                            map[enemy.row][enemy.col] = '.';

                        Position next = path[1];

                        if (map[next.row][next.col] != 'D')
                        {
                            enemy = next;
                            map[enemy.row][enemy.col] = 'E';
                        }
                        else
                        {
                            enemy = next;
                        }
                    }
                }
            }

        
            map[destination.row][destination.col] = 'D';

            
            if (active)
            {
                if (checkWin(player, destination))
                {
                    gameWin = true;
                    score += 100;
                    if (score > bestScore) bestScore = score;
                }

                if (checkLose(player, enemy))
                    gameOver = true;
            }

            
            if (timerStarted && active)
                elapsedTime = GetTime() - startTime;

            
            if ((gameOver || gameWin) && round < maxRounds && IsKeyPressed(KEY_R))
            {
                round++;
                resetGame(map, &player, &destination, &enemy,
                          &score, &startTime, &gameOver, &gameWin, &timerStarted);
            }

            
            if ((gameOver || gameWin) && round == maxRounds)
                gameState = END;

        
            DrawRectangleGradientV(0, 0, screenWidth, TOP_BAR,
                                   Color{40,40,45,255},
                                   Color{10,10,10,255});

            int section = screenWidth / 4;

            DrawText(TextFormat("Score: %d", score), 30, 25, 24, WHITE);
            DrawText(TextFormat("Time: %.1f", elapsedTime), section + 30, 25, 24, SKYBLUE);
            DrawText(TextFormat("Best: %d", bestScore), section*2 + 30, 25, 24, GREEN);
            DrawText(TextFormat("Round: %d/%d", round, maxRounds), section*3 + 30, 25, 24, ORANGE);

            
            for(int i = 0; i < ROWS; i++)
            {
                for(int j = 0; j < COLS; j++)
                {
                    int x = j * CELL_SIZE;
                    int y = i * CELL_SIZE + TOP_BAR;

                    Color tile = ((i + j) % 2 == 0)
                                 ? Color{210,210,210,255}
                                 : Color{190,190,190,255};

                    DrawRectangle(x+3, y+3, CELL_SIZE, CELL_SIZE, Fade(BLACK, 0.15f));
                    DrawRectangle(x, y, CELL_SIZE, CELL_SIZE, tile);

                    if(map[i][j] == '#')
                        DrawRectangle(x, y, CELL_SIZE, CELL_SIZE, DARKGRAY);

                    else if(map[i][j] == 'D')
                    {
                        float pulse = 2 * sin(GetTime()*3);

                        DrawCircle(x + CELL_SIZE/2, y + CELL_SIZE/2,
                                   CELL_SIZE/3 + 8 + pulse, Fade(BLUE, 0.2f));

                        DrawCircle(x + CELL_SIZE/2, y + CELL_SIZE/2,
                                   CELL_SIZE/3, BLUE);

                        DrawCircle(x + CELL_SIZE/2, y + CELL_SIZE/2,
                                   CELL_SIZE/6, SKYBLUE);
                    }

                    else if(map[i][j] == 'P')
                    {
                        float pulse = 3 * sin(GetTime()*5);

                        DrawCircle(x + CELL_SIZE/2, y + CELL_SIZE/2,
                                   CELL_SIZE/3 + 6, Fade(GREEN, 0.2f));

                        DrawCircle(x + CELL_SIZE/2, y + CELL_SIZE/2,
                                   CELL_SIZE/3 + pulse, GREEN);
                    }

                    else if(map[i][j] == 'E')
                    {
                        DrawCircle(x + CELL_SIZE/2, y + CELL_SIZE/2,
                                   CELL_SIZE/3 + 5, Fade(RED, 0.2f));

                        DrawCircle(x + CELL_SIZE/2, y + CELL_SIZE/2,
                                   CELL_SIZE/3 - 2, RED);

                        DrawCircle(x + CELL_SIZE/2, y + CELL_SIZE/2,
                                   CELL_SIZE/8, Color{139,0,0,255});
                    }
                }
            }

            
            if (gameWin && round < maxRounds)
            {
                DrawRectangle(screenWidth/2 - 180, screenHeight/2 - 40,
                              360, 80, Fade(BLACK, 0.7f));

                DrawText("YOU WIN! Press R",
                         screenWidth/2 - 150,
                         screenHeight/2 - 10,
                         30,
                         LIME);
            }

    
            if (gameOver && round < maxRounds)
            {
                DrawRectangle(screenWidth/2 - 180, screenHeight/2 - 40,
                              360, 80, Fade(BLACK, 0.7f));

                DrawText("GAME OVER! Press R",
                         screenWidth/2 - 160,
                         screenHeight/2 - 10,
                         30,
                         RED);
            }
        }

     
        else if (gameState == END)
        {
            DrawText("ALL ROUNDS COMPLETE!", screenWidth/2 - 220, 180, 40, YELLOW);
            DrawText(TextFormat("BEST SCORE: %d", bestScore),
                     screenWidth/2 - 180, 260, 30, GREEN);

            DrawText("Press ENTER to Restart", screenWidth/2 - 180, 340, 22, WHITE);

            if (IsKeyPressed(KEY_ENTER))
                gameState = MENU;
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}