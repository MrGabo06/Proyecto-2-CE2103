#include "raylib.h"
#include "raymath.h"
#include "include/player.h"

int main(void)
{
    const int screenWidth = 1500;
    const int screenHeight = 750;
    InitWindow(screenWidth, screenHeight, "Selda");
    Player player(500, 100);

    int currentFrame = 0;
    const int frameSpeed = 8;
    int frameCounter = 0;

    Rectangle frameRec = {0.0f, 0.0f, (float) player.currentSpriteSheet.width/4, (float)player.currentSpriteSheet.height};

    while (!WindowShouldClose())
    {
        float frameTime = GetFrameTime();
        player.movePlayer(frameTime);

        BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawTextureRec(player.currentSpriteSheet, frameRec, player.getPosition(), WHITE);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
