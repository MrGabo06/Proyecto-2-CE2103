#include "raylib.h"
#include "raymath.h"
#include "include/player.h"
#include "include/Map.h"
#include "include/MapChunk.h"

int main(void) {
    const int screenWidth = 1500;
    const int screenHeight = 750;

    InitWindow(screenWidth, screenHeight, "Selda");
    Player player(500, 100);

    float chunk_sizes[] = {(float)player.currentSpriteSheet.width / 1.5, (float)player.currentSpriteSheet.width / 1.5};
    Map2D map(Level::second, chunk_sizes);
        map.generate();
        map.locate_at(&player, 2, 4); 

    int currentFrame = 0;
    const int frameSpeed = 8;
    int frameCounter = 0;

    Rectangle frameRec = {0.0f, 0.0f, (float)player.currentSpriteSheet.width / 4, (float)player.currentSpriteSheet.height};

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
        EndMode2D();

        BeginDrawing();
            
        EndDrawing();
    }

    CloseWindow();

    return 0;
}