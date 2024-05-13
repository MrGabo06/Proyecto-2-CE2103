#include "treasure.h"

Treasure::Treasure(){
    this->setHealthPoints(1);
    this->setPosition(0, 0);
    this->currentSpriteSheet = movingDownSprite;
}

Treasure::Treasure(float xCord, float yCord){
    this->setHealthPoints(5);
    this->setPosition(xCord, yCord);
    this->currentSpriteSheet = movingDownSprite;
}