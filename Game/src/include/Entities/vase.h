#ifndef VASE_H
#define VASE_H

#include <raylib.h>
#include "../Entity.h"

/// @brief Class for creating vase entities that contain loot
class Vase : public Entity{
public: // Attributes
    const Texture2D vaseTexture = LoadTexture("Game/src/resources/entity_assets/vase.png");
public: // Methods

    /// @brief Default constructor
    Vase();

    /// @brief Constructor for class
    /// @param xCord 
    /// @param yCord 
    Vase(int xCord, int yCord);
};

#endif // VASE_H