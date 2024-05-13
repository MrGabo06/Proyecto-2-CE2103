#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <raylib.h>
#include "../Entity.h"
using namespace std;

#define PLAYER_JUMP_SPD 200.0f
#define PLAYER_HOR_SPD 200.0f

/// @brief Class for player entity that can be controlled by user
class Player : public Entity {
private: //Attributes
    int cellSize = 0;
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
public: // Methods

    /// @brief Create an instance of Player class
    /// @param xCord: The starting horizontal coords of the player
    /// @param yCord: The starting vertical coords of the player 
    /// @param currentMapCellSize: The size of each cell of the map
    Player(float xCord, float yCord, int currentMapCellSize);

    /// @brief Moves the player and checks it doesnt overpass the limits of the map
    /// @param frameTime: Raylib window frame time
    /// @param mapSize: Map width and height
    void movePlayer(float frameTime, int mapSize[2]);

    /// @brief Set the size of each map cell to the given value
    /// @param currentMapCellSize: The new cell size to be established
    void setMapCellSize(int currentMapCellSize);

    /// @brief Sets the limits of the map so the player doesnt move out of it
    /// @param limits: Maximum X and Y limits
    void setMapLimits(int limits[2]);

};

#endif // PLAYER_H
