#include "treasure.h"

Treasure::Treasure(){
    this->healthPoints = 0;
    this->setPosition(0.f, 0.f);
    this->currentSpriteSheet = treasureTexture;
}

Treasure::Treasure(int xCord, int yCord){
    this->healthPoints = 0;
    this->setPosition(0.f, 0.f);
    this->graphX = xCord;
    this->graphY = yCord;
    this->currentSpriteSheet = treasureTexture;
}