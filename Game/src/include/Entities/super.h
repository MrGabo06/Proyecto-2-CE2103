#ifndef SUPER_H
#define SUPER_H

#include <raylib.h>
#include "../Enemy.h"

/// @brief Class for creating a super enemy type that works as a special enemy of the temple
class Super : public Enemy {
public: //Attributes
    const Texture2D movingUpSprite = LoadTexture("Game/src/resources/player_assets/playerUp.png");
    const Texture2D movingDownSprite = LoadTexture("Game/src/resources/player_assets/playerDown.png");
    const Texture2D movingLeftSprite = LoadTexture("Game/src/resources/player_assets/playerLeft.png");
    const Texture2D movingRightSprite = LoadTexture("Game/src/resources/player_assets/playerRight.png");   

public: // Methods

    /// @brief Default constructor
    Super(){
        this->setHealthPoints(1);
        this->setPosition(0, 0);
        this->currentSpriteSheet = movingDownSprite;
    }

    /// @brief Constructor for class
    /// @param xCord 
    /// @param yCord 
    Super(float xCord, float yCord){
        this->setHealthPoints(5);
        this->setPosition(xCord, yCord);
        this->currentSpriteSheet = movingDownSprite;
    }
};

#endif // SUPER_H
