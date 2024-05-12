#include "raylib.h"
#include "raymath.h"
#include "include/player.h"
#include "include/Map.h"
#include "include/MapChunk.h"
#include "include/Entidades/rat.hpp" 
#include "include/Entidades/ojoespectral.hpp"
#include "include/Entidades/espectro.hpp"
#include "include/Entidades/jefe.hpp"
#include "include/Entidades/chocobo.hpp"


int main(void) {
    const int screenWidth = 1500;
    const int screenHeight = 750;

    InitWindow(screenWidth, screenHeight, "Selda");
    Player player(500, 100);

    Rat rat(700, 200);

    ojo ojo(700, 300);

    espectro espectro(700, 400);

    jefe jefe(700, 500);

    chocobo chocobo(700, 600);

    float chunk_sizes[] = {(float)player.currentSpriteSheet.width, (float)player.currentSpriteSheet.width};
    Map2D map(Level::first, chunk_sizes);
        map.generate();
        map.locate_at(&player, 2, 4); 

    int currentFrame = 0;
    const int frameSpeed = 8;
    int frameCounter = 0;

    Rectangle frameRec = {0.0f, 0.0f, (float)player.currentSpriteSheet.width/4, (float)player.currentSpriteSheet.height};

    Camera2D camera = { 0 };
    camera.target = (Vector2){ player.getPosition().x + 20.f, player.getPosition().y + 20.f};
    camera.offset = (Vector2){ screenWidth/4, screenHeight/4};
    camera.rotation = 0.0f;
    camera.zoom = 1.5f;

    SetTargetFPS(60);
    while (!WindowShouldClose()){
        ClearBackground(RAYWHITE);

        float frameTime = GetFrameTime();
        player.movePlayer(frameTime);

        camera.target = (Vector2){ player.getPosition().x + 40.f, player.getPosition().y + 20.f};

        BeginMode2D(camera);
            for (int i = 0; i<map.grid_size[0]; i++){
                for (int j = 0; j<map.grid_size[1]; j++){
                    MapChunk chunk = map.get(i,j);
                    Rectangle chunkRec = {0.0f, 0.0f, chunk.size[0], chunk.size[1]};
                    DrawTextureRec(chunk.texture, chunkRec, chunk.position, RAYWHITE);
                }
            }
            DrawTextureRec(player.currentSpriteSheet, frameRec, player.getPosition(), WHITE);
            DrawTextureRec(rat.currentSpriteSheet, frameRec, rat.getPosition(), WHITE); // Dibujamos al ratón
        EndMode2D();

        BeginDrawing();
            
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
