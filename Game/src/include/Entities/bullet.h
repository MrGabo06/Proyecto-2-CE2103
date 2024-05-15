#ifndef BULLET_H
#define BULLET_H

#include <raylib.h>
#include "../Enemy.h"

/// @brief Class for creating bird enemy type
class Bullet : public Enemy
{
public: // Attributes
    const Texture2D movingLeftSprite = LoadTexture("Game/src/resources/enemy_assets/Firebal.png");
    const Texture2D movingRightSprite = LoadTexture("Game/src/resources/enemy_assets/Firebal.png");

public: // Methods
    /// @brief Default constructor method
    Bullet();

    /// @brief Constructor method
    /// @param xCord
    /// @param yCord
    Bullet(float xCord, float yCord);
    void shoot(MapChunk &playerPosition, float frameTime);
};

#endif // BULLET_H