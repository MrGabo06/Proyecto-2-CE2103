#include "super.h"
#include <iostream>
Super::Super()
{
    this->setHealthPoints(1);
    this->setPosition(0, 0);
    this->currentSpriteSheet = movingDownSprite;
}

Super::Super(float xCord, float yCord)
{
    this->setHealthPoints(5);
    this->setPosition(xCord, yCord);
    this->currentSpriteSheet = movingDownSprite;
}
void Super::hola()
{
    cout << "Hola" << endl;
}
