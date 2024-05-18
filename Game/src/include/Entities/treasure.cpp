#include "treasure.h"

Treasure::Treasure(){
    this->setHealthPoints(1);
    this->setPosition(0.f, 0.f);
    this->currentSpriteSheet = treasureTexture;
}

Treasure::Treasure(int xCord, int yCord){
    this->setHealthPoints(1);
    this->setPosition(0.f, 0.f);
    this->graphX = xCord;
    this->graphY = yCord;
    this->currentSpriteSheet = treasureTexture;
}