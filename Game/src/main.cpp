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
#include "controller.h"
#include <glog/logging.h>

int main(){
	  google::InitGoogleLogging("Selda");
	  LOG(INFO) << "Logging initialized!";
  
    const int screenWidth = 1500;
    const int screenHeight = 750;
    const Level rotation[] = {Level::first, Level::second, Level::third, Level::fourth, Level::fifth};
    int sp[] = {1, 1, 1, 1, 0, 7, 7};
    //          ^SP ^Y ^R ^C ^SU ^T ^V
    int level = 0;

    Controller* gameController = nullptr;
    char controllerEntry;

    // Controller reader module
    // gameController = new Controller();
    // controllerEntry = gameController->entry;
    
    // To not read the controller inputs
    controllerEntry = 'u';

    InitWindow(screenWidth, screenHeight, "Selda");

    // { BASIC INITIALIZATION }
    Player player(1, 1);

    float chunk_sizes[] = {(float)player.cellSize, (float)player.cellSize};
    Map2D map(rotation[level], chunk_sizes);
      map.generate();
      map.locate_at(&player, player.graphY, player.graphX, true);
      player.currentMap = &map;

    Manager computer(&map, sp[0], sp[1], sp[2], sp[3], sp[4], sp[5], sp[6]);
  
    LinkedList<MapChunk> breadcrumbList;
        player.breadcrumbs = &breadcrumbList;
    Queue<MapChunk> lightList;

    // init minimap
    Texture2D minimaps[5];
    Vector2 minimap_pos[5];
    std::string map_asset = "Game/src/resources/map_assets/minimap";
    for (int i = 0; i < 5; i++){
    	std::string asset = map_asset + std::to_string(i) + ".png";
    	const char* c_str = asset.c_str();
    	
    	Image image = LoadImage(c_str);
    	ImageResize(&image, image.width/4, image.height/4);
    	minimaps[i] = LoadTextureFromImage(image);
    	UnloadImage(image);
    	
    	Vector2 mm_pos;
    	mm_pos.x = 0;
    	mm_pos.y = screenHeight - minimaps[i].height;
    	minimap_pos[i] = mm_pos;
    }

    // { FRAME PARAMETERS }
    int currentFrame = 0;
    const int frameSpeed = 5;
    int frameCounter = 0;
    int enemyCurrentFrame = 0;
    int enemyFrameCounter = 0;
  
    // { TEXTURE RECTANGLE }
    Rectangle playerFrameRect = {0.0f, 0.0f, (float)player.currentSpriteSheet.width / 4, (float)player.currentSpriteSheet.height};
    Rectangle enemyFrameRect = {0.0f, 0.0f, (float)player.currentSpriteSheet.width / 4, (float)player.currentSpriteSheet.height};

    /// { CAMERA INITIALIZATION }
    Camera2D camera = {0};
    camera.offset = (Vector2){screenWidth / 4, screenHeight / 4};
    camera.rotation = 0.0f;
    camera.zoom = 0.5f; // Camera limits are set for 3.5f zoom

    SetTargetFPS(120);
    auto startTime = std::chrono::steady_clock::now();
    while (!WindowShouldClose())
    {
        if(gameController != nullptr){
            controllerEntry = gameController->entry;
        }
        auto currentTime = std::chrono::steady_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime).count();
        ClearBackground(RAYWHITE);

        // *****************************************
        // Behind logic
        // *****************************************

        float frameTime = GetFrameTime();
        player.movePlayer(frameTime, controllerEntry);

        if (player.getPosition().x < 207.0f)
        {
            camera.target.x = 107.0f;
        } else if (player.getPosition().x > 1843.0f){
            camera.target.x = 1740.0f;
        } else{
            camera.target.x = player.getPosition().x - 100.0f;
        }

        if (player.getPosition().y < 85.0f){
            camera.target.y = 55.0f;
        } else if (player.getPosition().y > 732.0f){
            camera.target.y = 702.0f;
        } else {
            camera.target.y = player.getPosition().y - 30.0f;
        }

        map.locate_at(&player, player.graphY, player.graphX, false);

        if (player.getHealth() <= 0){
            break;
        }

        if (map.get(player.graphY, player.graphX).breadcrumb == 0 && player.isMoving && breadcrumbList.getSize() < 10)
        {
            breadcrumbList.insert(map.get(player.graphY, player.graphX));
            map.get(player.graphY, player.graphX).breadcrumb = 1;
        }

        if (player.isMoving && breadcrumbList.getSize() == 10)
        {
            breadcrumbList.get(breadcrumbList.getSize() - 1).breadcrumb = 0;
            breadcrumbList.remove(breadcrumbList.getSize() - 1);

            breadcrumbList.insert(map.get(player.graphY, player.graphX));
        }

        cout << breadcrumbList.getSize() << endl;

        // if (map.get(player.graphY, player.graphX).light == false && player.isMoving && lightList.size() < 2000)
        // {
        //     lightList.enqueue(map.get(player.graphY, player.graphX));
        //     // lightList.enqueue(map.get(player.graphY + 1, player.graphX));
        // }

        // else if (player.isMoving && lightList.size() > 2000)
        // {
        //     lightList.enqueue(map.get(player.graphY, player.graphX));
        //     lightList.dequeue();
        // }
        // cout << lightList.size() << endl;
      
        // *******************************************
        // Transitions between levels
        // *******************************************
        if (IsKeyDown(KEY_ENTER) || controllerEntry == 'e')
        {
            if (player.getLocation()->data.chunk_type == ChunkType::gate)
            {
                level++;
                computer.killAll(elapsedTime);
                map.regenerate(rotation[level], chunk_sizes);
                if (level == 0)
                {
                    computer.evolve(1, 0, 0, 0, 0, 0, 0);
                }
                else if (level == 1)
                {
                    computer.evolve(1, 0, 0, 0, 0, 0, 0);
                }
                else if (level == 2)
                {
                    computer.evolve(1, 0, 0, 0, 0, 0, 0);
                }
                else if (level == 3)
                {
                    computer.evolve(1, 0, 0, 0, 0, 0, 0);
                }
                else if (level == 4)
                {
                    computer.evolve(1, 0, 0, 0, 0, 0, 0);
                }
                map.locate_at(&player, 1, 1, true);
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
                for (int x = 0; x < lightList.size(); x++)
                {
                    if (chunk == lightList.get(x))
                    {
                        chunk.lightChunk();
                    }
                    else
                    {
                        chunk.unLightChunk();
                    }
                }
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

            if (currentFrame > 3){
                currentFrame = 0;
            }

            playerFrameRect.x = (float)currentFrame * (float)player.currentSpriteSheet.width / 4;
        }

        enemyFrameCounter++;

        if (enemyFrameCounter >= (60 / frameSpeed))
        {
            enemyFrameCounter = 0;
            enemyCurrentFrame++;

            if (enemyCurrentFrame > 3)
            {
                enemyCurrentFrame = 0;
            }

            enemyFrameRect.x = (float)enemyCurrentFrame * (float)player.currentSpriteSheet.width / 4;
        }
      
        // *******************************************
        // Enemy drawing and behavior
        // *******************************************

        for (int i = 0; i < computer.size(EntGroup::enemies); i++){
            Enemy *enemy = static_cast<Enemy *>(computer.getEntity(EntGroup::enemies, i));
            enemy->shift(frameTime, elapsedTime);
            if (enemy->rangeToEntity(&player, false) && !player.isSafe()){
                enemy->setTarget(&player);
                enemy->engage();
            }

            if (i >= sp[0] + sp[1] + sp[2] + sp[3] && i < sp[0] + sp[1] + sp[2] + sp[3] + sp[4]){
                Super *boss = static_cast<Super *>(enemy);
                boss->bullet->shoot(player.getLocation()->data, frameTime);
                map.locate_at(boss->bullet, boss->bullet->graphY, boss->bullet->graphX, false);
                if (abs(boss->bullet->getPosition().x - player.getPosition().x) < 40 && abs(boss->bullet->getPosition().y - player.getPosition().y) < 40 && boss->bullet->hit == false)
                {
                    boss->bullet->deleteBull(boss->getPosition().x, boss->getPosition().y);
                    player.addHealthPoints(-1);
                }

                DrawTextureRec(boss->bullet->movingLeftSprite, playerFrameRect, boss->bullet->getPosition(), WHITE);
            }
          
            if ( i < sp[0]+sp[1] && i >= sp[0] ){
                for (int a = 0; a < sp[0]; a++){
                    Enemy *specter = static_cast<Enemy *>(computer.getEntity(EntGroup::enemies, a));
                    if (enemy->rangeToEntity(&player, false) && !player.isSafe()){
                        specter->setTarget(&player);
                        specter->engage();
                    }
                }
            }
          
            if (i < sp[1] && i > 0){
                for (int a = sp[0] + sp[1]; a < sp[0] + sp[1] + sp[2]; a++){
                    Enemy *rat = static_cast<Enemy *>(computer.getEntity(EntGroup::enemies, a));
                    if (enemy->rangeToEntity(rat, false)){
                        enemy->disengage();
                    }
                }
            }
            if ( i < sp[0]+sp[1] && i >= sp[0] ){
                for (int a = 0; a < sp[0]; a++){
                    Enemy *specter = static_cast<Enemy *>(computer.getEntity(EntGroup::enemies, a));
                    if (enemy->rangeToEntity(&player, false) && !player.isSafe()){
                        specter->setTarget(&player);
                        specter->engage();
                    }
                }
            }
            enemy->shift(frameTime, elapsedTime);
            map.locate_at(enemy, enemy->graphY, enemy->graphX, false);
          
            if (enemy->getHealth() > 0){
                if ((IsKeyDown(KEY_SPACE) || controllerEntry == 'v') && std::abs(enemy->getPosition().x - player.getPosition().x) < 40.0f && std::abs(enemy->getPosition().y - player.getPosition().y) < 40.0f)
                {
                    player.attack(enemy, elapsedTime);
                    player.addCoins(1);
                } else if(IsKeyDown(KEY_SPACE)){
                  player.attack(nullptr, 0.0f);
                }
              
                Rectangle rect = {0.f, 0.f, (float)enemy->currentSpriteSheet.width / 4, (float)enemy->currentSpriteSheet.height};
                DrawTextureRec(enemy->currentSpriteSheet, rect, enemy->getPosition(), RAYWHITE);
            }
        }

        // *******************************************
        // Vases and treasures behavior
        // *******************************************
        for (int i = 0; i < computer.size(EntGroup::statical); i++){
            Entity *ent = computer.getEntity(EntGroup::statical, i);
            if (ent->getHealth() > 0){
                DrawTexture(ent->currentSpriteSheet, ent->getPosition().x, ent->getPosition().y, RAYWHITE);
                if ((IsKeyDown(KEY_SPACE) || controllerEntry == 'v') && std::abs(ent->getPosition().x - player.getPosition().x) < 40.0f && std::abs(ent->getPosition().y - player.getPosition().y) < 40.0f)
                {
                    player.attackE(ent);
                    player.addCoins(1);
                } else if(IsKeyDown(KEY_SPACE)){
                    player.attackE(nullptr);
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
      
        // minimap drawing
        DrawTexture(minimaps[level], minimap_pos[level].x, minimap_pos[level].y, WHITE);
		    DrawCircle(player.getPosition().x/8, screenHeight - screenHeight/5.8 + player.getPosition().y/8, 3, RED);
        // Dibujar monedas
        DrawTexture(player.CointSprite, 40, 60, WHITE);
        // Contador de monedas
        std::string coinsText = "Coins: " + std::to_string(player.getCoins());
        DrawText(coinsText.c_str(), 40 + player.CointSprite.width + 10, 60, 20, BLACK);
      
        EndDrawing();

    }

    CloseWindow();
  
//     if(gameController!= nullptr){
//         gameController->playing = false;
//         gameController->controllerThread.join();
//     }
	  google::ShutdownGoogleLogging();
  
    return 0;
}
