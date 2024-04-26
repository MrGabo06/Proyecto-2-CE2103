#include <iostream>
#include "raylib.h"
#include "entity.h"
using namespace std;

#define PLAYER_JUMP_SPD 200.0f
#define PLAYER_HOR_SPD 200.0f

class Player : public Entity {
private:
    //Attributes
    

public:
    //Attributes
    const Texture2D movingUpSprite = LoadTexture("gameAssets/playerSprites/playerUp.png");
    const Texture2D movingDownSprite = LoadTexture("gameAssets/playerSprites/playerDown.png");
    const Texture2D movingLeftSprite = LoadTexture("gameAssets/playerSprites/playerLeft.png");
    const Texture2D movingRightSprite = LoadTexture("gameAssets/playerSprites/playerRight.png");   

    Texture2D currentSpriteSheet = movingDownSprite;

    //Constructor
    Player(float xCord, float yCord)
    {
        this->setHealthPoints(5);
        this->setPosition(xCord, yCord);
    }

    //Methods
    void movePlayer(float frameTime)
    {
        if (!IsKeyDown(KEY_LEFT) && !IsKeyDown(KEY_RIGHT) && !IsKeyDown(KEY_UP) && !IsKeyDown(KEY_DOWN))
        {
            // Stop movement
        }

        if (IsKeyDown(KEY_UP))
        {
            this->move(frameTime, Entity::mvUp);
            this->currentSpriteSheet = movingUpSprite;
        }

        if (IsKeyDown(KEY_DOWN))
        {
            this->move(frameTime, Entity::mvDown);
            this->currentSpriteSheet = movingDownSprite;
        }

        if (IsKeyDown(KEY_LEFT))
        {
            this->move(frameTime, Entity::mvLeft);
            this->currentSpriteSheet = movingLeftSprite;
        }

        if (IsKeyDown(KEY_RIGHT))
        {
            this->move(frameTime, Entity::mvRight);
            this->currentSpriteSheet = movingRightSprite;
        }
    }

};
