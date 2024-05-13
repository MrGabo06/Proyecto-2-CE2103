#ifndef CHOCOBO_H
#define CHOCOBO_H

#include <raylib.h>
#include "../Enemy.h"

/// @brief Class for creating bird enemy type
class Chocobo : public Enemy {
public: // Attributes
    const Texture2D movingUpSprite = LoadTexture("Game/src/resources/player_assets/playerUp.png");
    const Texture2D movingDownSprite = LoadTexture("Game/src/resources/player_assets/playerDown.png");
    const Texture2D movingLeftSprite = LoadTexture("Game/src/resources/player_assets/playerLeft.png");
    const Texture2D movingRightSprite = LoadTexture("Game/src/resources/player_assets/playerRight.png");   

public: // Methods
    
    /// @brief Default constructor method
    Chocobo();

    /// @brief Constructor method
    /// @param xCord 
    /// @param yCord 
    Chocobo(float xCord, float yCord);

};

#endif // CHOCOBO_H
