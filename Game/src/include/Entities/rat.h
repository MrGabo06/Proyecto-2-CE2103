#ifndef RAT_H
#define RAT_H

#include <raylib.h>
#include "../Enemy.h"

/// @brief Class for creating rat enemy type
class Rat : public Enemy {
public: //Attributes
    const Texture2D movingUpSprite = LoadTexture("Game/src/resources/player_assets/playerUp.png");
    const Texture2D movingDownSprite = LoadTexture("Game/src/resources/player_assets/playerDown.png");
    const Texture2D movingLeftSprite = LoadTexture("Game/src/resources/player_assets/playerLeft.png");
    const Texture2D movingRightSprite = LoadTexture("Game/src/resources/player_assets/playerRight.png");   

public: // Methods
    
    /// @brief Default constructor for the class
    Rat();

    /// @brief Constructor for the class
    /// @param xCord 
    /// @param yCord 
    Rat(float xCord, float yCord);

};

#endif // RAT_H