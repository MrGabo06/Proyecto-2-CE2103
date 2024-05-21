#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <raylib.h>
#include "../Entity.h"
#include "../Map.h"
using namespace std;

#define PLAYER_JUMP_SPD 200.0f
#define PLAYER_HOR_SPD 200.0f

/// @brief Class for player entity that can be controlled by user
class Player : public Entity{
private: // Attributes
    int worldUpLimit = 0;
    int worldDownLimit = 0;
    int worldLeftLimit = 0;
    int worldRightLimit = 0;
    
    const Texture2D movingUpSprite = LoadTexture("Game/src/resources/player_assets/playerUp.png");
    const Texture2D movingDownSprite = LoadTexture("Game/src/resources/player_assets/playerDown.png");
    const Texture2D movingLeftSprite = LoadTexture("Game/src/resources/player_assets/playerLeft.png");
    const Texture2D movingRightSprite = LoadTexture("Game/src/resources/player_assets/playerRight.png");
  
    const Texture2D attackDownSprite = LoadTexture("Game/src/resources/player_assets/playAttackDown.png");
    const Texture2D attackUpSprite = LoadTexture("Game/src/resources/player_assets/playAttackUp.png");
    const Texture2D attackLeftSprite = LoadTexture("Game/src/resources/player_assets/playAttackLeft.png");
    const Texture2D attackRightSprite = LoadTexture("Game/src/resources/player_assets/playAttackRight.png");
  
    MapChunk *above = nullptr;
    MapChunk *below = nullptr;
    MapChunk *left = nullptr;
    MapChunk *right = nullptr;
    MapChunk *belowRight = nullptr;
    MapChunk *aboveRight = nullptr;
    MapChunk *belowLeft = nullptr;

public:
    bool light = false;
    bool isMoving;

    int graphAbove = 0, graphBelow = 0, graphLeft = 0, graphRight = 0;
    float aboveLimit = 0.0f, belowLimit = 0.0f, leftLimit = 0.0f, rightLimit = 0.0f, downRightLimit = 0.0f;
    Map2D *currentMap = nullptr;

    const Texture2D idleSprite2 = LoadTexture("Game/src/resources/player_assets/fullheartShield.png");
    const Texture2D idleSprite = LoadTexture("Game/src/resources/player_assets/fullheart.png");

public: // Methods

    /// @brief Make the player attack
    /// @param frameTime: Raylib window frame time
    void attack();

    /// @brief Create an instance of Player class
    /// @param startingGraphX: The starting horizontal graph coords of the player
    /// @param startingGraphY: The starting vertical graph coords of the player
    Player(int startingGraphX, int startingGraphY);

    /// @brief Override from the original Entity "move" method to add map colliders
    /// @param frameTime: Raylib window frame time
    /// @param dir: Direction the player will move to
    void move(float frameTime, const char dir) override;

    /// @brief Moves the player and checks it doesnt overpass the limits of the map
    /// @param frameTime: Raylib window frame time
    void movePlayer(float frameTime);

    /// @brief Sets the limits of the map so the player doesnt move out of it
    /// @param limits: Maximum X and Y limits
    void setMapLimits(int limits[2]);


};

#endif // PLAYER_H
