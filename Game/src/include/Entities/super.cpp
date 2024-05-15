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

void Super::movePattern(int mov)
{
    if (mov == 1)
    {
        this->setPosition(this->getPosition().x + 0.5f, this->getPosition().y + 0.5f);
    }
    else if (mov == 2)
    {
        this->setPosition(this->getPosition().x - 0.5f, this->getPosition().y - 0.5f);
    }
    else if (mov == 3)
    {
        this->setPosition(this->getPosition().x - 0.5f, this->getPosition().y);
    }
    else if (mov == 4)
    {
        this->setPosition(this->getPosition().x + 0.5f, this->getPosition().y);
    }
    else if (mov == 5)
    {
        this->setPosition(this->getPosition().x, this->getPosition().y + 0.5);
    }
    else if (mov == 6)
    {
        this->setPosition(this->getPosition().x, this->getPosition().y - 0.5);
    }
}

void Super::attackPattern(int atk)
{
    if (atk == 1)
    {
        Bullet bullet(this->getPosition().x, this->getPosition().y);
    }
}
