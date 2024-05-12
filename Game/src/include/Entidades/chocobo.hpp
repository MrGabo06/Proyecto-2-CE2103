#ifndef CHOCOBO_H
#define CHOCOBO_H

#include <iostream>
#include <raylib.h>
#include "entity.h"
using namespace std;

#define PLAYER_JUMP_SPD 200.0f
#define PLAYER_HOR_SPD 200.0f

class chocobo : public Entity {
private:
    //Attributes

public:
    //Attributes
    const Texture2D movingUpSprite = LoadTexture("Game/src/resources/player_assets/playerUp.png");
    const Texture2D movingDownSprite = LoadTexture("Game/src/resources/player_assets/playerDown.png");
    const Texture2D movingLeftSprite = LoadTexture("Game/src/resources/player_assets/playerLeft.png");
    const Texture2D movingRightSprite = LoadTexture("Game/src/resources/player_assets/playerRight.png");   

    Texture2D currentSpriteSheet = movingDownSprite;

    //Constructor
    chocobo(float xCord, float yCord)
   {
        this->setHealthPoints(5);
        this->setPosition(xCord, yCord);
    }
    Vector2 getPosition() {
        return this->position;
    }

};

#endif // CHOCOBO_H
