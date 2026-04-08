#include <stdio.h>
#include <limits.h>
#include "map.h"
#include "DAA.h"


int bfsSoundWave(char map[ROWS][COLS], Position start, Position target)
{
    int visited[ROWS][COLS] = {0};

    Position queue[ROWS * COLS];
    int front = 0, rear = 0;

    queue[rear++] = start;
    visited[start.row][start.col] = 1;

    int dRow[] = {-1, 1, 0, 0};
    int dCol[] = {0, 0, -1, 1};

    while (front < rear)
    {
        Position cur = queue[front++];

        
        if (cur.row == target.row && cur.col == target.col)
            return 1;

        for (int i = 0; i < 4; i++)
        {
            int nr = cur.row + dRow[i];
            int nc = cur.col + dCol[i];

            if (nr >= 0 && nr < ROWS &&
                nc >= 0 && nc < COLS &&
                !visited[nr][nc] &&
                map[nr][nc] != '#')
            {
                visited[nr][nc] = 1;
                queue[rear++] = (Position){nr, nc};
            }
        }
    }

    return 0; 
}

 
int dijkstraPath(char map[ROWS][COLS],
                 Position start,
                 Position target,
                 Position path[])
{
    int dist[ROWS][COLS];
    Position parent[ROWS][COLS];

    
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            dist[i][j] = INT_MAX;
            parent[i][j] = (Position){-1, -1};
        }
    }


    int visited[ROWS][COLS] = {0};

    dist[start.row][start.col] = 0;

    int dRow[] = {-1, 1, 0, 0};
    int dCol[] = {0, 0, -1, 1};

    
    for (int count = 0; count < ROWS * COLS; count++)
    {
        int minDist = INT_MAX;
        Position u = {-1, -1};

        
        for (int i = 0; i < ROWS; i++)
        {
            for (int j = 0; j < COLS; j++)
            {
                if (!visited[i][j] && dist[i][j] < minDist)
                {
                    minDist = dist[i][j];
                    u = (Position){i, j};
                }
            }
        }

        if (u.row == -1)
            break;

        visited[u.row][u.col] = 1;

        
        for (int i = 0; i < 4; i++)
        {
            int nr = u.row + dRow[i];
            int nc = u.col + dCol[i];

            if (nr >= 0 && nr < ROWS &&
                nc >= 0 && nc < COLS &&
                map[nr][nc] != '#')
            {
                if (dist[nr][nc] > dist[u.row][u.col] + 1)
                {
                    dist[nr][nc] = dist[u.row][u.col] + 1;
                    parent[nr][nc] = u;
                }
            }
        }
    }

    
    int length = 0;
    Position cur = target;

    while (cur.row != -1)
    {
        path[length++] = cur;
        cur = parent[cur.row][cur.col];
    }

    
    for (int i = 0; i < length / 2; i++)
    {
        Position temp = path[i];
        path[i] = path[length - i - 1];
        path[length - i - 1] = temp;
    }

    return length;
}