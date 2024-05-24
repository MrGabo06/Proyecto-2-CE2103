#include "raylib.h"
#include "raymath.h"
#include "include/Entities/player.h"
#include "include/Map.h"
#include "include/MapChunk.h"
#include "include/Manager.h"
#include "include/Enemy.h"
#include <chrono>
#include <iostream>
#include "modules/LinkedList.h"
#include "modules/Node.hpp"

int main(){
    const int screenWidth = 1500;
    const int screenHeight = 750;

    InitWindow(screenWidth, screenHeight, "Selda");

    float chunk_sizes[] = {(float)48, (float)48};
    Map2D map(Level::first, chunk_sizes);
    int currentLevel = 1;
    map.generate();

    Manager computer(&map, 5, 0, 0, 0, 0, 0, 1);
    LinkedList<MapChunk> breadcrumbList;

    Player player(1, 1);
    player.currentMap = &map;
    player.breadcrumbs = &breadcrumbList;
    map.locate_at(&player, player.graphY, player.graphX, true);

    int currentFrame = 0;
    const int frameSpeed = 5;
    int frameCounter = 0;

    Rectangle playerFrameRect = {0.0f, 0.0f, (float)player.currentSpriteSheet.width / 4, (float)player.currentSpriteSheet.height};

    Camera2D camera = {0};
    camera.offset = (Vector2){screenWidth / 4, screenHeight / 4};
    camera.rotation = 0.0f;

    // Camera limits are set for 3.5f zoom
    camera.zoom = 3.5f;

    SetTargetFPS(120);
    auto startTime = std::chrono::steady_clock::now();
    while (!WindowShouldClose()){
        auto currentTime = std::chrono::steady_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime).count();
        ClearBackground(RAYWHITE);

        // *****************************************
        // Behind logic
        // *****************************************

        float frameTime = GetFrameTime();
        player.movePlayer(frameTime);

        if (player.getPosition().x < 207.0f){
            camera.target.x = 107.0f;
        }
        else if (player.getPosition().x > 1843.0f){
            camera.target.x = 1740.0f;
        }
        else{
            camera.target.x = player.getPosition().x - 100.0f;
        }

        if (player.getPosition().y < 85.0f){
            camera.target.y = 55.0f;
        }
        else if (player.getPosition().y > 732.0f){
            camera.target.y = 702.0f;
        }
        else{
            camera.target.y = player.getPosition().y - 30.0f;
        }

        map.locate_at(&player, player.graphY, player.graphX, false);

        if (player.getHealth() <= 0)
        {
            break;
        }

        if (map.get(player.graphY, player.graphX).breadcrumb == 0 && player.isMoving && breadcrumbList.getSize() < 20)
        {
            breadcrumbList.insert(map.get(player.graphY, player.graphX));
            map.get(player.graphY, player.graphX).breadcrumb = 1;
        }

        if (player.isMoving && breadcrumbList.getSize() > 20)
        {   
            breadcrumbList.get(breadcrumbList.getSize()-1).breadcrumb = 0;
            breadcrumbList.remove(breadcrumbList.getSize()-1);

            breadcrumbList.insert(map.get(player.graphY, player.graphX));
        }

        cout << breadcrumbList.getSize() << endl;

        // *******************************************
        // Trasnsitions between levels
        // *******************************************
        if (IsKeyDown(KEY_N))
        {
            if (map.get(player.graphY, player.graphX).exit)
            {
                if (currentLevel == 1)
                {
                    map.regenerate(Level::second, chunk_sizes);
                }
                else if (currentLevel == 2)
                {
                    map.regenerate(Level::third, chunk_sizes);
                }
                else if (currentLevel == 3)
                {
                    map.regenerate(Level::fourth, chunk_sizes);
                }
                else if (currentLevel == 4)
                {
                    map.regenerate(Level::fifth, chunk_sizes);
                }
                currentLevel++;
            }
            else if (map.get(player.graphY, player.graphX).exit)
            {
                if (currentLevel == 2)
                {
                    map.regenerate(Level::first, chunk_sizes);
                }
                else if (currentLevel == 3)
                {
                    map.regenerate(Level::second, chunk_sizes);
                }
                else if (currentLevel == 4)
                {
                    map.regenerate(Level::third, chunk_sizes);
                }
                else if (currentLevel == 5)
                {
                    map.regenerate(Level::fourth, chunk_sizes);
                }
                currentLevel--;
            }
        }
        // ------------------------------------------------------------------------------------------------
        BeginMode2D(camera);

        // *******************************************
        // Drawing Section
        // *******************************************
        BeginMode2D(camera);
        for (int i = 0; i < map.grid_size[0]; i++)
        {
            for (int j = 0; j < map.grid_size[1]; j++)
            {
                MapChunk &chunk = map.get(i, j);
                Rectangle chunkRec = {0.0f, 0.0f, chunk.size[0], chunk.size[1]};
                DrawTextureRec(chunk.texture, chunkRec, chunk.position, RAYWHITE);
            }
        }

        // *******************************************
        // Animation Logic
        // *******************************************

        frameCounter++;

        if (frameCounter >= (60 / frameSpeed))
        {
            if (!player.isMoving)
            {
                currentFrame = 0;
            }
            else
            {
                frameCounter = 0;
                currentFrame++;
            }

            if (currentFrame > 3)
                currentFrame = 0;

            playerFrameRect.x = (float)currentFrame * (float)player.currentSpriteSheet.width / 4;
        }
            if(player.isAtacking){
                
                if (!player.isAnimation)
                {
                    player.isAnimation = true;
                    currentFrame = 0;
                }
                if(player.isAnimation && currentFrame + 1 % 4 == 0){
                    player.isAnimation = false;
                    player.isAtacking = false;
                }
            }

        // *******************************************
        // Enemy drawing and behavior
        // *******************************************

        for (int i = 0; i < computer.size(EntGroup::enemies); i++){
            Enemy *enemy = static_cast<Enemy *>(computer.getEntity(EntGroup::enemies, i));
            if (enemy->rangeToEntity(&player, false)){
                enemy->setTarget(&player);
                enemy->engage();
            }
            if (IsKeyDown(KEY_SPACE) && std::abs(enemy->getPosition().x - player.getPosition().x) < 40.0f && std::abs(enemy->getPosition().y - player.getPosition().y) < 40.0f)
            {
                player.attack(enemy);
            }
            if (enemy->isAtacking && std::abs(enemy->getPosition().x - player.getPosition().x) < 40.0f && std::abs(enemy->getPosition().y - player.getPosition().y) < 40.0f)
            {
                enemy->attack();
            }

            enemy->shift(frameTime, elapsedTime);
            map.locate_at(enemy, enemy->graphY, enemy->graphX, false);
            if (enemy->getHealth() > 0){
                DrawTextureRec(enemy->currentSpriteSheet, playerFrameRect, enemy->getPosition(), RAYWHITE);
            }
        }

        // *******************************************
        // Vases and treasures behavior
        // *******************************************
        for (int i = 0; i < computer.size(EntGroup::statical); i++){
            Entity *ent = computer.getEntity(EntGroup::statical, i);

            if (ent->getHealth() > 0)
            {
                DrawTexture(ent->currentSpriteSheet, ent->getPosition().x, ent->getPosition().y, RAYWHITE);

                if (IsKeyDown(KEY_SPACE) && std::abs(ent->getPosition().x - player.getPosition().x) < 40.0f && std::abs(ent->getPosition().y - player.getPosition().y) < 40.0f)
                {
                    player.attackE(ent);
                }
            }
        }

        // *******************************************
        // Player drawing Logic
        // *******************************************
        DrawTextureRec(player.currentSpriteSheet, playerFrameRect, player.getPosition(), WHITE);
        EndMode2D();

        // ------------------------------------------------------------------------------------------------

        BeginDrawing();
      
        int heartOffset = 40; // Offset entre cada corazón
        int shieldOffset = 40; // Offset entre cada escudo
        int heartStartPosX = 40; // Posición inicial en X para los corazones
        int shieldStartPosX = heartStartPosX + (player.getHealth() * heartOffset); // Posición inicial en X para los escudos

        // Dibujar corazones
        for (int i = 0; i < player.getHealth(); i++) {
            DrawTexture(player.idleSprite, heartStartPosX + (heartOffset * i), 10, WHITE);
        }

        // Dibujar escudos
        for (int i = 0; i < player.getShield(); i++) {
            DrawTexture(player.idleSprite2, shieldStartPosX + (shieldOffset * i), 10, WHITE);
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}