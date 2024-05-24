#ifndef SPECTER_H
#define SPECTER_H

#include <raylib.h>
#include "../Enemy.h"
#include "../../modules/patterns/Observer.h"

/// @brief Class for creating a 'guardian specter' for the temple levels
class Specter : public Enemy, public Observer {
public:
    //Attributes
    const Texture2D movingUpSprite = LoadTexture("Game/src/resources/entity_assets/graySpecterUp.png");
    const Texture2D movingDownSprite = LoadTexture("Game/src/resources/entity_assets/graySpecterDown.png");
    const Texture2D movingLeftSprite = LoadTexture("Game/src/resources/entity_assets/graySpecterLeft.png");
    const Texture2D movingRightSprite = LoadTexture("Game/src/resources/entity_assets/graySpecterRight.png");
    
public: // Methods

    /// @brief Default constructor
    Specter();

    /// @brief Constructor method
    /// @param xCord: x coordinate of entity
    /// @param yCord: y coordinate of entity
    /// @param skill_rates: array(6) of attributes for scaling the difficulty of this enemy
    Specter(int xCord, int yCord, int skill_rates[]);

    void update() override {};
    
private:
    /// @brief Sets the enemy properties based on a rating (1-10) 
    /// @param scaling: array(6) of ratings
    void setProperties(int scaling[]) override;
};

#endif // SPECTER_H
