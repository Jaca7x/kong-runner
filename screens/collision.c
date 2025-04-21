
#include "collision.h"
#include <stdlib.h>
#include "../librays/raylib.h"

void collision(int meters) {
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        const int fontSizeTitle = 40;
        const int fontSizeInfo = 20;

        DrawText("GAME OVER", (400 - MeasureText("GAME OVER", fontSizeTitle)), 140, fontSizeTitle, RED);
        DrawText(TextFormat("VOCÊ CHEGOU A %d METROS", meters), (300 - MeasureText("VOCÊ CHEGOU A", fontSizeInfo)), 200, fontSizeInfo, RED);
        DrawText("CLIQUE ESC PARA SAIR", (400 - MeasureText("CLIQUE ESC PARA SAIR", fontSizeInfo)), 240, fontSizeInfo, RED);
        EndDrawing();
        if (IsKeyDown(KEY_ESCAPE))
    {
        break;
    }
    }
    CloseWindow();
    exit(0);
}
