#ifndef SUPER_H
#define SUPER_H

#include <raylib.h>
#include "../Enemy.h"
#include <iostream>
#include <ctime>
#include "bullet.h"

/// @brief Class for creating a super enemy type that works as a special enemy of the temple
class Super : public Enemy
{
private: // Attributes
    const Texture2D movingUpSprite = LoadTexture("Game/src/resources/enemies_assets/boss.png");
    const Texture2D movingDownSprite = LoadTexture("Game/src/resources/enemies_assets/boss.png");
    const Texture2D movingLeftSprite = LoadTexture("Game/src/resources/enemies_assets/boss.png");
    const Texture2D movingRightSprite = LoadTexture("Game/src/resources/enemies_assets/boss.png");
    MapChunk &playerPosition;
    float frameTime;
    static MapChunk defaultChunk;
    Bullet *bullet = nullptr;
    LinkedList<Bullet *> bulletList;
    Rectangle frameRec;

public: // Methods
    /// @brief Default constructor
    Super();

    /// @brief Constructor method
    /// @param xCord: x coordinate of entity
    /// @param yCord: y coordinate of entity
    /// @param skill_rates: array(6) of attributes for scaling the difficulty of this enemy
    Super(int xCord, int yCord, int skill_rates[]);

    void movePattern(int mov);

    void attackPattern(int atk);

    void getPlayerPosition(MapChunk &actualPosition, float frameTime);

    void shift(float frame_time, int64_t time_stamp) override;

private:
    /// @brief Sets the enemy properties based on a rating (1-10)
    /// @param scaling: array(6) of ratings
    void setProperties(int scaling[]) override;
};

#endif // SUPER_H
