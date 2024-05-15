#include "raylib.h"
#include "raymath.h"
#include "include/Entities/player.h"
#include "include/Map.h"
#include "include/MapChunk.h"
#include "include/Manager.h"
#include "modules/LinkedList.h"
#include "modules/Node.hpp"

int main()
{
    const int screenWidth = 1500;
    const int screenHeight = 750;

    InitWindow(screenWidth, screenHeight, "Selda");

    float chunk_sizes[] = {(float)48, (float)48};
    Map2D map(Level::first, chunk_sizes);
    map.generate();

    Manager computer(&map, 5, 2, 2, 3, 1, 5, 5);
    LinkedList<MapChunk> breadcrumbList;

    Player player(4, 2);
    map.locate_at(&player, player.graphY, player.graphX, true);

    player.setMapLimits(map.grid_size);

    int currentFrame = 0;
    const int frameSpeed = 8;
    int frameCounter = 0;

    Rectangle frameRec = {0.0f, 0.0f, (float)player.currentSpriteSheet.width / 4, (float)player.currentSpriteSheet.height};

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
        player.movePlayer(frameTime);

        camera.target = (Vector2){player.getPosition().x - 75.0f, player.getPosition().y - 30.0f};

        map.locate_at(&player, player.graphY, player.graphY, false);

        MapChunk breadcrumb = map.get(player.graphY, player.graphX);

        if (map.get(player.graphY, player.graphX).breadcrumb == 0 && player.isMoving && breadcrumbList.getSize() < 20)
        {
            breadcrumbList.insert(breadcrumb);
            map.get(player.graphY, player.graphX).breadcrumb = 1;
        }

        else if (player.isMoving && breadcrumbList.getSize() > 20)
        {
            breadcrumbList.insert(breadcrumb);
            breadcrumbList.remove(0);
        }

        cout
            << breadcrumbList.getSize() << endl;

        // Enemy* testEnemy = static_cast<Enemy*>(computer.getEntity(enemies, 0));
        // testEnemy->moveTo(map.get(player.graphY, player.graphX), frameTime);

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

        for (int i = 0; i < computer.size(EntGroup::enemies); i++)
        {
            Enemy *enemy = static_cast<Enemy *>(computer.getEntity(EntGroup::enemies, i));
            enemy->moveTo(map.get(player.graphY, player.graphX), frameTime);
            DrawTextureRec(enemy->currentSpriteSheet, frameRec, enemy->getPosition(), RAYWHITE);
        }

        for (int i = 0; i < computer.size(EntGroup::statical); i++)
        {
            Entity *ent = computer.getEntity(EntGroup::statical, i);
            DrawTextureRec(ent->currentSpriteSheet, frameRec, ent->getPosition(), RAYWHITE);
        }
        DrawTextureRec(player.currentSpriteSheet, frameRec, player.getPosition(), WHITE);
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
