#ifndef VASE_H
#define VASE_H

#include <raylib.h>
#include "../Entity.h"

/// @brief Class for creating vase entities that contain loot
class Vase : public Entity{
public: // Attributes
    const Texture2D movingUpSprite = LoadTexture("Game/src/resources/player_assets/playerUp.png");
    const Texture2D movingDownSprite = LoadTexture("Game/src/resources/player_assets/playerDown.png");
    const Texture2D movingLeftSprite = LoadTexture("Game/src/resources/player_assets/playerLeft.png");
    const Texture2D movingRightSprite = LoadTexture("Game/src/resources/player_assets/playerRight.png");   
public: // Methods

    /// @brief Default constructor
    Vase(){
        this->setHealthPoints(1);
        this->setPosition(0, 0);
        this->currentSpriteSheet = movingDownSprite;
    };

    /// @brief Constructor for class
    /// @param xCord 
    /// @param yCord 
    Vase(float xCord, float yCord){
        this->setHealthPoints(5);
        this->setPosition(xCord, yCord);
        this->currentSpriteSheet = movingDownSprite;
    };
};

#endif // VASE_H