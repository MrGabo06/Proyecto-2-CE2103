#include "rat.h"

Rat::Rat(){
    this->setHealthPoints(1);
    this->setPosition(0, 0);
    this->currentSpriteSheet = movingDownSprite;
}

Rat::Rat(float xCord, float yCord){
    this->setHealthPoints(5);
    this->setPosition(xCord, yCord);
    this->currentSpriteSheet = movingDownSprite;
}