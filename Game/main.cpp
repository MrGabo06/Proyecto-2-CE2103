#include "raylib.h"
#include "raymath.h"
#include "include/player.h"

int main(void)
{
    const int screenWidth = 1500;
    const int screenHeight = 750;
    InitWindow(screenWidth, screenHeight, "Selda");
    Player player(500, 100, "sprites/goku.png");

    while (!WindowShouldClose())
    {
        float deltaTime = GetFrameTime();
        player.UpdatePlayer(&player, deltaTime);

        BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawTexture(player.getSprite(), player.getPosition().x, player.getPosition().y, WHITE);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
