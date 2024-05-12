#ifndef EYE_H
#define EYE_H

#include <raylib.h>
#include "../Enemy.h"
#include "../../modules/patterns/Observer.h"

/// @brief Class for creating guardian spectral eyes that alert specters of intruders
class Eye : public Enemy, public Observable {
public: // Attributes
    const Texture2D movingUpSprite = LoadTexture("Game/src/resources/player_assets/playerUp.png");
    const Texture2D movingDownSprite = LoadTexture("Game/src/resources/player_assets/playerDown.png");
    const Texture2D movingLeftSprite = LoadTexture("Game/src/resources/player_assets/playerLeft.png");
    const Texture2D movingRightSprite = LoadTexture("Game/src/resources/player_assets/playerRight.png");   

public: // Methods

    /// @brief Default constructor
    Eye(){
        this->setHealthPoints(1);
        this->setPosition(0, 0);
        this->currentSpriteSheet = movingDownSprite;
    };

    /// @brief Constructor class
    /// @param xCord 
    /// @param yCord 
    Eye(float xCord, float yCord){
        this->setHealthPoints(5);
        this->setPosition(xCord, yCord);
        this->currentSpriteSheet = movingDownSprite;
    };
};

#endif // EYE_H
