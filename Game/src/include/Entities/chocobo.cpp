#include "chocobo.h"

Chocobo::Chocobo(){
    this->setHealthPoints(1);
    this->setPosition(0,0);
    this->currentSpriteSheet = movingDownSprite;
}

Chocobo::Chocobo(float xCord, float yCord){
        this->setHealthPoints(5);
        this->setPosition(xCord, yCord);
        this->currentSpriteSheet = movingDownSprite;
    }
