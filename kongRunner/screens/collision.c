
#include "collision.h"
#include "librays/raylib.h"

void collision(int meters, int screenHeight, int screenWidth) {
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        const int fontSizeTitle = 40;
        const int fontSizeInfo = 20;

        DrawText("GAME OVER", (screenWidth - MeasureText("GAME OVER", fontSizeTitle)), 140, fontSizeTitle, RED);
        DrawText(TextFormat("VOCÊ CHEGOU A %d METROS", meters), (screenWidth - MeasureText("VOCÊ CHEGOU A", fontSizeInfo)) + 30, 200, fontSizeInfo, RED);
        DrawText("CLIQUE ESC PARA SAIR", (screenWidth - MeasureText("CLIQUE ESC PARA SAIR", fontSizeInfo)), 240, fontSizeInfo, RED);

        EndDrawing();
    }
}
