#ifndef TREASURE_H
#define TREASURE_H

#include <raylib.h>
#include "../Entity.h"

/// @brief Class for creating treasure entities that contain gold(points)
class Treasure : public Entity{
public: // Attributes
    const Texture2D treasureTexture = LoadTexture("Game/src/resources/entitys_assets/chest.png");
public: // Methods

    /// @brief Default constructor
    Treasure();

    /// @brief Constructor for class
    /// @param xCord 
    /// @param yCord 
    Treasure(float xCord, float yCord);
};

#endif // TREASURE_H