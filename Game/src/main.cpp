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

int main(void)
{
    const int screenWidth = 1500;
    const int screenHeight = 750;

    InitWindow(screenWidth, screenHeight, "Selda");
    Rat rat(700, 200);

    ojo ojo(700, 300);

    espectro espectro(700, 400);

    jefe jefe(700, 500);

    chocobo chocobo(700, 600);

    int graphX = 2;
    int graphY = 4;

    float chunk_sizes[] = {(float)48, (float)48};

    Player player(500, 100, chunk_sizes[0]);

    Map2D map(Level::second, chunk_sizes);
    map.generate();
    map.locate_at(&player, graphX, graphY, true);

    player.setMapLimits(map.grid_size);

    int currentFrame = 0;
    const int frameSpeed = 8;
    int frameCounter = 0;

    Rectangle frameRec = {0.0f, 0.0f, (float)player.currentSpriteSheet.width / 4, (float)player.currentSpriteSheet.height};

    Camera2D camera = {0};
    camera.target = (Vector2){player.getPosition().x, player.getPosition().y};
    camera.offset = (Vector2){screenWidth / 4, screenHeight / 4};
    camera.rotation = 0.0f;
    camera.zoom = 4.5f;

    SetTargetFPS(120);
    while (!WindowShouldClose())
    {
        ClearBackground(RAYWHITE);

        float frameTime = GetFrameTime();
        player.movePlayer(frameTime, map.grid_size);

        graphX = player.getPosition().x / chunk_sizes[0];
        graphY = player.getPosition().y / chunk_sizes[0];

        camera.target = (Vector2){player.getPosition().x - 75.0f, player.getPosition().y - 30.0f};

        map.locate_at(&player, graphY, graphX, false);

        BeginMode2D(camera);
        for (int i = 0; i < map.grid_size[0]; i++)
        {
            for (int j = 0; j < map.grid_size[1]; j++)
            {
                MapChunk chunk = map.get(i, j);
                Rectangle chunkRec = {0.0f, 0.0f, chunk.size[0], chunk.size[1]};
                DrawTextureRec(chunk.texture, chunkRec, chunk.position, RAYWHITE);
            }
        }

        if (player.light && map.get(graphY + 1, graphX).light == false && map.get(graphY - 1, graphX).light == false && map.get(graphY, graphX - 1).light == false && map.get(graphY, graphX + 1).light == false)
        {
            map.get(graphY + 1, graphX).lightChunk();
            map.get(graphY - 1, graphX).lightChunk();
            map.get(graphY, graphX - 1).lightChunk();
            map.get(graphY, graphX + 1).lightChunk();
            map.get(graphY, graphX).lightChunk();
            for (int i = 0; i < map.grid_size[0]; i++)
            {
                for (int j = 0; j < map.grid_size[1]; j++)
                {
                    if (i > graphX - 2 && map.get(i, j).light)
                    {
                        map.get(i, j).unLightChunk();
                    }
                    else if (i < graphX + 2 && map.get(i, j).light)
                    {
                        map.get(i, j).unLightChunk();
                    }
                    else if (j > graphY + 2 && map.get(i, j).light)
                    {
                        map.get(i, j).unLightChunk();
                    }
                    else if (j < graphY - 2 && map.get(i, j).light)
                    {
                        map.get(i, j).unLightChunk();
                    }
                }
            }
        }
        else if (map.get(graphY + 1, graphX).light && map.get(graphY - 1, graphX).light && map.get(graphY, graphX - 1).light && map.get(graphY, graphX + 1).light)
        {
            map.get(graphY + 1, graphX).unLightChunk();
            map.get(graphY - 1, graphX).unLightChunk();
            map.get(graphY, graphX - 1).unLightChunk();
            map.get(graphY, graphX + 1).unLightChunk();
            map.get(graphY, graphX).unLightChunk();
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
