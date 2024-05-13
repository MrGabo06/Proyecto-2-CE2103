#include "specter.h"

Specter::Specter(){
    this->setHealthPoints(1);
    this->setPosition(0, 0);
    this->currentSpriteSheet = movingDownSprite;
};

Specter::Specter(float xCord, float yCord){
    this->setHealthPoints(5);
    this->setPosition(xCord, yCord);
    this->currentSpriteSheet = movingDownSprite;
}