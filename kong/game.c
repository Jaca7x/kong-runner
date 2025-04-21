#include "game.h"
#include "../utils/map.h"
#include "../screens/collision.h"
#include "../librays/raylib.h"
#include <stdlib.h>

#define MAX_OBSTACLES 5
#define PLAYER_JUMP_SPD 350.0f
#define GRAVITY 500.0f

Texture2D background, donk, rock, donkJump;
Rectangle dest;
Rectangle obstacles[MAX_OBSTACLES];
Rectangle source, sourceJump;
Vector2 origin = {0, 0};
float groundX1 = 0, groundX2 = 0;
float scrollSpeed = 300.0f;
float playerSpeed = 0.0f;
bool jump = true;
int meters = 0;
int frameWidth, frameHeight, frameWidthJump, frameHeightJump;
float animTimer = 0.0f;
int currentFrame = 0;
const int cols = 3, rows = 1;
const int totalFrame = 3;
const float animFPS = 5.0f;

void InitGameResources() {
    background = LoadTexture("resources/background.png");
    Image img = LoadImage("resources/gorilla_sheet.png");
    Image imgRock = LoadImage("resources/rock.png");
    Image imgJump = LoadImage("resources/gorilla_sheet_jump.png");

    ImageColorReplace(&img, WHITE, BLANK);
    ImageColorReplace(&imgRock, WHITE, BLANK);
    ImageColorReplace(&imgJump, WHITE, BLANK);

    donk = LoadTextureFromImage(img);
    UnloadImage(img);
    rock = LoadTextureFromImage(imgRock);
    UnloadImage(imgRock);
    donkJump = LoadTextureFromImage(imgJump);
    UnloadImage(imgJump);

    groundX2 = background.width;

    frameWidth = donk.width / cols;
    frameHeight = donk.height / rows;
    frameWidthJump = donkJump.width / cols;
    frameHeightJump = donkJump.height / rows;

    source = (Rectangle){0, 0, frameWidth, frameHeight};
    sourceJump = (Rectangle){0, 0, frameWidthJump, frameHeightJump};

    dest = (Rectangle){575 / 2.0f, 300.0f, 64.0f, 64.0f};

    // Aumentando a distância entre os obstáculos
    for (int i = 0; i < MAX_OBSTACLES; i++) {
        obstacles[i] = (Rectangle){575 + i * rand(), 310, 50.0f, 50.0f}; // Aumentado o espaçamento para 500
    }
}

void UpdateGame(float deltaTime) {
    animTimer += deltaTime;
    if (animTimer >= 1.0f / animFPS) {
        currentFrame = (currentFrame + 1) % totalFrame;
        animTimer -= 1.0f / animFPS;
    }

    source.x = currentFrame * frameWidth;
    sourceJump.x = currentFrame * frameWidthJump;
    sourceJump.y = currentFrame * frameHeightJump;

    if (IsKeyDown(KEY_SPACE) && jump) {
        playerSpeed = -PLAYER_JUMP_SPD;
        jump = false;
    }

    playerSpeed += GRAVITY * deltaTime;
    dest.y += playerSpeed * deltaTime;

    if (dest.y >= 300) {
        dest.y = 300;
        playerSpeed = 0;
        jump = true;
    }

    for (int i = 0; i < MAX_OBSTACLES; i++) {
        obstacles[i].x -= scrollSpeed * deltaTime;
        if (obstacles[i].x + obstacles[i].width < 0) {
            obstacles[i].x = 575 + rand() % 200;
        }

        if (CheckCollisionRecs(dest, obstacles[i])) {
            if ((dest.y + dest.height) <= obstacles[i].y && playerSpeed > 0) {
                dest.y = obstacles[i].y - dest.height;
                playerSpeed = 0;
                jump = true;
            } else {
                collision(meters);
            }
        }
    }

    meters += dest.x / 250;
    updateMap(&groundX1, &groundX2, scrollSpeed, deltaTime, background.width);
}

void DrawGame() {
    BeginDrawing();
    ClearBackground(WHITE);

    DrawTexture(background, (int)groundX1, 409 - background.height, WHITE);
    DrawTexture(background, (int)groundX2, 409 - background.height, WHITE);

    for (int i = 0; i < MAX_OBSTACLES; i++) {
        Rectangle src = {0, 0, rock.width, rock.height};
        Rectangle dst = obstacles[i];
        Vector2 orig = {0.0f, 10.0f};
        DrawTexturePro(rock, src, dst, orig, 0.0f, WHITE);
    }

    if (jump) {
        DrawTexturePro(donk, source, dest, origin, 0.0f, RAYWHITE);
    } else {
        DrawTexturePro(donkJump, sourceJump, dest, origin, 0.0f, RAYWHITE);
    }

    DrawText(TextFormat("Metros: %d", meters), 10, 10, 20, RED);

    EndDrawing();
}

void UnloadGameResources() {
    UnloadTexture(background);
    UnloadTexture(donk);
    UnloadTexture(rock);
    UnloadTexture(donkJump);
}
