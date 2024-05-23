#ifndef CHOCOBO_H
#define CHOCOBO_H

#include <raylib.h>
#include "../Enemy.h"

/// @brief Class for creating bird enemy type
class Chocobo : public Enemy {
public: // Attributes
    const Texture2D movingUpSprite = LoadTexture("Game/src/resources/entity_assets/cochoLeft.png");
    const Texture2D movingDownSprite = LoadTexture("Game/src/resources/entity_assets/cochoLeft.png");
    const Texture2D movingLeftSprite = LoadTexture("Game/src/resources/entity_assets/cochoLeft.png");
    const Texture2D movingRightSprite = LoadTexture("Game/src/resources/entity_assets/cochoLeft.png");

public: // Methods
    
    /// @brief Default constructor method
    Chocobo();

    /// @brief Constructor method
    /// @param xCord: x coordinate of entity
    /// @param yCord: y coordinate of entity
    /// @param skill_rates: array(6) of attributes for scaling the difficulty of this enemy
    Chocobo(int xCord, int yCord, int skill_rates[]);

private:
    /// @brief Sets the enemy properties based on a rating (1-10) 
    /// @param scaling: array(6) of ratings
    void setProperties(int scaling[]) override;

};

#endif // CHOCOBO_H
