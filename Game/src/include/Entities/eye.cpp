#include "eye.h"

Eye::Eye() {
    this->setHealthPoints(1);
    this->setPosition(0, 0);
    this->currentSpriteSheet = movingDownSprite;
}

Eye::Eye(float xCord, float yCord){
    this->setHealthPoints(5);
    this->setPosition(xCord, yCord);
    this->currentSpriteSheet = movingDownSprite;
}