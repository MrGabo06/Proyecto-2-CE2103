#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <raylib.h>
#include "../Entity.h"
using namespace std;

#define PLAYER_JUMP_SPD 200.0f
#define PLAYER_HOR_SPD 200.0f

/// @brief Class for player entity that can be controlled by user
class Player : public Entity{
private: // Attributes
    int upLimit = 0;
    int downLimit = 0;
    int leftLimit = 0;
    int rightLimit = 0;

public:
    const Texture2D movingUpSprite = LoadTexture("Game/src/resources/player_assets/playerUp.png");
    const Texture2D movingDownSprite = LoadTexture("Game/src/resources/player_assets/playerDown.png");
    const Texture2D movingLeftSprite = LoadTexture("Game/src/resources/player_assets/playerLeft.png");
    const Texture2D movingRightSprite = LoadTexture("Game/src/resources/player_assets/playerRight.png");
    const Texture2D idleSprite = LoadTexture("Game/src/resources/player_assets/fullheart.png");
    bool light = false;
    bool isMoving;

public: // Methods
    /// @brief Create an instance of Player class
    /// @param startingGraphX: The starting horizontal graph coords of the player
    /// @param startingGraphY: The starting vertical graph coords of the player
    Player(int startingGraphX, int startingGraphY);

    /// @brief Moves the player and checks it doesnt overpass the limits of the map
    /// @param frameTime: Raylib window frame time
    void movePlayer(float frameTime);

    /// @brief Sets the limits of the map so the player doesnt move out of it
    /// @param limits: Maximum X and Y limits
    void setMapLimits(int limits[2]);
};

#endif // PLAYER_H
