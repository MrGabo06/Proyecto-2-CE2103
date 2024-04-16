#include <iostream>
#include "raylib.h"
using namespace std;

#define PLAYER_JUMP_SPD 350.0f
#define PLAYER_HOR_SPD 200.0f

class Player
{
private:
    Vector2 position;
    Texture2D playerSprites[10];
    int currentSpriteIndex;

public:
    Player(float xInicial, float yInicial, const char *sprite)
    {
        position = {xInicial, yInicial};
        playerSprites[0] = LoadTexture("sprites/img1.png");
        playerSprites[1] = LoadTexture("sprites/img2.png");
        playerSprites[2] = LoadTexture("sprites/img3.png");
        playerSprites[3] = LoadTexture("sprites/img4.png");
        playerSprites[0] = LoadTexture("sprites/img5.png");
        playerSprites[1] = LoadTexture("sprites/img6.png");
        playerSprites[2] = LoadTexture("sprites/img7.png");
        playerSprites[3] = LoadTexture("sprites/img8.png");
        playerSprites[3] = LoadTexture("sprites/img9.png");

        int currentSpriteIndex = 1;
    }

    Texture2D getSprite()
    {
        return playerSprites[currentSpriteIndex];
    }

    Vector2 getPosition()
    {
        return position;
    }

    void UpdatePlayer(Player *player, float delta)
    {
        if (!IsKeyDown(KEY_LEFT) && !IsKeyDown(KEY_RIGHT) && !IsKeyDown(KEY_UP) && !IsKeyDown(KEY_DOWN))
        {
            // currentSpriteIndex = 4;
        }
        if (IsKeyDown(KEY_LEFT))
        {
            player->position.x -= PLAYER_HOR_SPD * delta;
            // UpdateSprite(-1);
        }

        if (IsKeyDown(KEY_RIGHT))
        {
            player->position.x += PLAYER_HOR_SPD * delta;
            // UpdateSprite(1);
        }

        if (IsKeyDown(KEY_UP))
        {
            player->position.y -= PLAYER_HOR_SPD * delta;
            // UpdateSprite(1);
        }

        if (IsKeyDown(KEY_DOWN))
        {
            player->position.y += PLAYER_HOR_SPD * delta;
            // UpdateSprite(-1);
        }
    }
    void UpdateSprite(int newState)
    {
        if (currentSpriteIndex <= 8 && currentSpriteIndex >= 1)
        {
            currentSpriteIndex = currentSpriteIndex + newState;
            cout << currentSpriteIndex << endl;
        }
        else
        {
            if (currentSpriteIndex > 8)
            {
                currentSpriteIndex = 1;
            }
            if (currentSpriteIndex < 1)
            {
                currentSpriteIndex = 8;
            }

            cout << currentSpriteIndex << endl;
        }
    }
};
