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
    Eye();

    /// @brief Constructor method
    /// @param xCord: x position of entity in Engine
    /// @param yCord: y position of entity in Engine
    /// @param skill_rates: array(6) of attributes for scaling the difficulty of this enemy
    Eye(float xCord, float yCord, int skill_rates[]);

private:
    /// @brief Sets the enemy properties based on a rating (1-10) 
    /// @param scaling: array(6) of ratings
    void setProperties(int scaling[]) override;
};

#endif // EYE_H
