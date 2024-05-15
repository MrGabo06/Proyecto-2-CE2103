#include "raylib.h"
#include "raymath.h"
#include "include/Entities/player.h"
#include "include/Map.h"
#include "include/MapChunk.h"
#include "include/Manager.h"

int main(void)
{
    const int screenWidth = 1500;
    const int screenHeight = 750;

    InitWindow(screenWidth, screenHeight, "Selda");

    float chunk_sizes[] = {(float)48, (float)48};
    Map2D map(Level::first, chunk_sizes);
    map.generate();

    int graphX = 2;
    int graphY = 4;

    Manager computer(&map, 0, 0, 0, 0, 1, 0, 0);

    Player player(500, 100, chunk_sizes[0]);
    map.locate_at(&player, graphY, graphX, true);
    Super *boss = static_cast<Super *>(computer.getEntity(enemies, 0));
    player.setMapLimits(map.grid_size);

    int currentFrame = 0;
    const int frameSpeed = 8;
    int frameCounter = 0;

    Rectangle frameRec = {0.0f, 0.0f, (float)player.currentSpriteSheet.width / 4, (float)player.currentSpriteSheet.height};
    Rectangle frameRec2 = {0.0f, 0.0f, (float)boss->currentSpriteSheet.width, (float)boss->currentSpriteSheet.height};

    Camera2D camera = {0};
    camera.target = (Vector2){player.getPosition().x, player.getPosition().y};
    camera.offset = (Vector2){screenWidth / 4, screenHeight / 4};
    camera.rotation = 0.0f;
    camera.zoom = 2.5f;

    SetTargetFPS(120);
    while (!WindowShouldClose())
    {
        ClearBackground(RAYWHITE);

        float frameTime = GetFrameTime();
        player.movePlayer(frameTime, map.grid_size);

        graphX = player.getPosition().x / chunk_sizes[0];
        graphY = player.getPosition().y / chunk_sizes[0];

        camera.target = (Vector2){player.getPosition().x - 75.0f, player.getPosition().y - 30.0f};

        map.locate_at(&player, player.graphY, player.graphX, false);

        boss->movePattern(6);
        boss->getPlayerPosition(map.get(player.graphY, player.graphX), frameTime); // Esto puede borrarlo

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
        // for (int i = 0; i < computer.size(EntGroup::enemies); i++)
        // {
        //     Enemy *enemy = static_cast<Enemy*>(computer.getEntity(EntGroup::enemies, i));
        //         enemy->shift();
        //     Rectangle frameRec2 = {0.0f, 0.0f, (float)enemy->currentSpriteSheet.width, (float)enemy->currentSpriteSheet.height};
        //     DrawTextureRec(enemy->currentSpriteSheet, frameRec2, enemy->getPosition(), RAYWHITE);
        // }

        // for (int i = 0; i < computer.size(EntGroup::statical); i++)
        // {
        //     Entity *ent = computer.getEntity(EntGroup::statical, i);
        //     DrawTextureRec(ent->currentSpriteSheet, frameRec, ent->getPosition(), RAYWHITE);
        // }

        DrawTextureRec(player.currentSpriteSheet, frameRec, player.getPosition(), WHITE);
        DrawTextureRec(boss->currentSpriteSheet, frameRec2, boss->getPosition(), WHITE);

        EndMode2D();

        BeginDrawing();
        for (int i = 1; i < player.getHealth() + 1; i++)
        {
            DrawTexture(player.idleSprite, 40 * i, 10, WHITE);
        }
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
