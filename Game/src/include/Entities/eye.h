#ifndef EYE_H
#define EYE_H

#include <raylib.h>
#include "../Enemy.h"
#include "../../modules/patterns/Observer.h"

/// @brief Class for creating guardian spectral eyes that alert specters of intruders
class Eye : public Enemy, public Observable {
public: // Attributes
    const Texture2D movingUpSprite = LoadTexture("Game/src/resources/enemies_assets/eye.png");
    const Texture2D movingDownSprite = LoadTexture("Game/src/resources/enemies_assets/eye.png");
    const Texture2D movingLeftSprite = LoadTexture("Game/src/resources/enemies_assets/eye.png");
    const Texture2D movingRightSprite = LoadTexture("Game/src/resources/enemies_assets/eye.png");   
    
public: // Methods

    /// @brief Default constructor
    Eye();

    /// @brief Constructor method
    /// @param xCord: x coordinate of entity
    /// @param yCord: y coordinate of entity
    /// @param skill_rates: array(6) of attributes for scaling the difficulty of this enemy
    Eye(int xCord, int yCord, int skill_rates[]);

    void setTarget(Entity* entity) override;
private:
    /// @brief Sets the enemy properties based on a rating (1-10) 
    /// @param scaling: array(6) of ratings
    void setProperties(int scaling[]) override;
};

#endif // EYE_H
