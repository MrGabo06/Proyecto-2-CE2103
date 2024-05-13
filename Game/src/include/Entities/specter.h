#ifndef SPECTER_H
#define SPECTER_H

#include <raylib.h>
#include "../Enemy.h"
#include "../../modules/patterns/Observer.h"

/// @brief Class for creating a 'guardian specter' for the temple levels
class Specter : public Enemy, public Observer {
public:
    //Attributes
    const Texture2D movingUpSprite = LoadTexture("Game/src/resources/player_assets/playerUp.png");
    const Texture2D movingDownSprite = LoadTexture("Game/src/resources/player_assets/playerDown.png");
    const Texture2D movingLeftSprite = LoadTexture("Game/src/resources/player_assets/playerLeft.png");
    const Texture2D movingRightSprite = LoadTexture("Game/src/resources/player_assets/playerRight.png");

public: // Methods

    /// @brief Default constructor
    Specter();

    /// @brief Constructor for class
    /// @param xCord 
    /// @param yCord 
    Specter(float xCord, float yCord);

    void update() override {};

};

#endif // SPECTER_H