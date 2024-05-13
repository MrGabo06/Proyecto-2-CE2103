#ifndef TREASURE_H
#define TREASURE_H

#include <raylib.h>
#include "../Entity.h"

/// @brief Class for creating treasure entities that contain gold(points)
class Treasure : public Entity{
public: // Attributes
    const Texture2D movingUpSprite = LoadTexture("Game/src/resources/player_assets/playerUp.png");
    const Texture2D movingDownSprite = LoadTexture("Game/src/resources/player_assets/playerDown.png");
    const Texture2D movingLeftSprite = LoadTexture("Game/src/resources/player_assets/playerLeft.png");
    const Texture2D movingRightSprite = LoadTexture("Game/src/resources/player_assets/playerRight.png");   
public: // Methods

    /// @brief Default constructor
    Treasure();

    /// @brief Constructor for class
    /// @param xCord 
    /// @param yCord 
    Treasure(float xCord, float yCord);
};

#endif // TREASURE_H