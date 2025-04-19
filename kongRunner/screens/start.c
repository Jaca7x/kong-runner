
#include "start.h"
#include "../librays/raylib.h"

extern Texture2D background;
extern float groundX1, groundX2;

void DrawStartScreen() {
    BeginDrawing();
    ClearBackground(BLACK);
    DrawTexture(background, (int)groundX1, 409 - background.height, WHITE);
    DrawTexture(background, (int)groundX2, 409 - background.height, WHITE);
    DrawText("KONG-RUNNER", GetScreenWidth() / 4, 140, 40, BLACK);
    DrawText("APERTE ENTER PARA JOGAR", 140, 200, 20, BLACK);
    EndDrawing();
}
