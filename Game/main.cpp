#include "raylib.h"
#include "raymath.h"



int main(void)
{
    const int screenWidth = 1500;
    const int screenHeight = 750;
    InitWindow(screenWidth, screenHeight, "Selda");

    while (!WindowShouldClose()) 
    {
        

        BeginDrawing();

        ClearBackground(RAYWHITE);

    
        EndDrawing();
    }


    CloseWindow();

    return 0;
}
