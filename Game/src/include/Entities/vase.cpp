#include "vase.h"

Vase::Vase(){
    this->setPosition(0,0);
    this->currentSpriteSheet = vaseTexture;
}

Vase::Vase(float xCord, float yCord){
    this->setPosition(xCord, yCord);
    this->currentSpriteSheet = vaseTexture;
    this->healthPoints = (1);
    
}

