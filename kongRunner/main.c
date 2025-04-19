#include "librays/raylib.h"
#include "game/game.h"
#include "utils/map.h"
#include "screens/start.h"
#include "screens/collision.h"
#include <stdlib.h>
#include <time.h>

int main()
{
    const int screenWidth = 575;
    const int screenHeight = 409;
    bool gameStart = false;

    InitWindow(screenWidth, screenHeight, "Kong Runner");
    SetTargetFPS(120);
    srand(time(NULL));

    InitGameResources(); // Carrega texturas e variáveis internas

    while (!WindowShouldClose())
    {
        float deltaTime = GetFrameTime();

        if (!gameStart)
        {
            DrawStartScreen(); // Você precisa mover isso para uma função nova dentro do game.c
            if (IsKeyPressed(KEY_ENTER)) gameStart = true;
            continue;
        }

        UpdateGame(deltaTime);
        DrawGame();
    }

    UnloadGameResources();
    CloseWindow();
    return 0;
}
