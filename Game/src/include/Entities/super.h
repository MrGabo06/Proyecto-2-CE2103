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
    Super();

    /// @brief Constructor method
    /// @param xCord: x position of entity in Engine
    /// @param yCord: y position of entity in Engine
    /// @param skill_rates: array(6) of attributes for scaling the difficulty of this enemy
    Super(float xCord, float yCord, int skill_rates[]);

private:
    /// @brief Sets the enemy properties based on a rating (1-10) 
    /// @param scaling: array(6) of ratings
    void setProperties(int scaling[]) override;
};

#endif // SUPER_H
