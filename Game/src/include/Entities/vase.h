#ifndef VASE_H
#define VASE_H

#include <raylib.h>
#include "../Entity.h"

/// @brief Class for creating vase entities that contain loot
class Vase : public Entity{
public: // Attributes
    const Texture2D vaseTexture = LoadTexture("Game/src/resources/entitys_assets/jarron.png");
public: // Methods

    /// @brief Default constructor
    Vase();

    /// @brief Constructor for class
    /// @param xCord 
    /// @param yCord 
    Vase(float xCord, float yCord);
};

#endif // VASE_H