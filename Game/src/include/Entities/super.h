#ifndef SUPER_H
#define SUPER_H

#include <raylib.h>
#include "../Enemy.h"

/// @brief Class for creating a super enemy type that works as a special enemy of the temple
class Super : public Enemy
{
public: // Attributes
    const Texture2D movingUpSprite = LoadTexture("Game/src/resources/enemies_assets/boss.png");
    const Texture2D movingDownSprite = LoadTexture("Game/src/resources/enemies_assets/boss.png");
    const Texture2D movingLeftSprite = LoadTexture("Game/src/resources/enemies_assets/boss.png");
    const Texture2D movingRightSprite = LoadTexture("Game/src/resources/enemies_assets/boss.png");

public: // Methods
    /// @brief Default constructor
    Super();

    /// @brief Constructor for class
    /// @param xCord
    /// @param yCord
    Super(float xCord, float yCord);

    void hola();
};

#endif // SUPER_H
