#include "vase.h"

Vase::Vase(){
    this->healthPoints = 1;
    this->setPosition(0.f,0.f);
    this->currentSpriteSheet = vaseTexture;
}

Vase::Vase(int xCord, int yCord){
    this->healthPoints = 1;
    this->setPosition(0.f, 0.f);
    this->graphX = xCord;
    this->graphY = yCord;
    this->currentSpriteSheet = vaseTexture;
}

