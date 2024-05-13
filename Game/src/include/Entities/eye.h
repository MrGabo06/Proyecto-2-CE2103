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
private:
    // Enemy subclass limit for attribute scaling
    const int MAX_DET_RANGE = 6;
    const int MAX_ROUTE_SIZE = 4;
    const int MAX_MOV_RANGE = 3;
    const float MAX_SPEED_MULT = 1.f;
    const int MAX_DECISIONS = 3;
    const int MAX_ATTACK_DMG = 2;
    
public: // Methods

    /// @brief Default constructor
    Eye();

    /// @brief Constructor method
    /// @param xCord: x position of entity in Engine
    /// @param yCord: y position of entity in Engine
    /// @param skill_rates: array(6) of attributes for scaling the difficulty of this enemy
    Eye(float xCord, float yCord, int skill_rates[]);
};

#endif // EYE_H
