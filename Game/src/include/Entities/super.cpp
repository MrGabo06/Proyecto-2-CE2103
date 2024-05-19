#include "super.h"
#include <iostream>

MapChunk Super::defaultChunk = MapChunk::defaultMapChunk();
Super::Super() : playerPosition(defaultChunk)
{
    this->setHealthPoints(1);
    this->setPosition(0, 0);
    this->currentSpriteSheet = movingDownSprite;
}

Super::Super(float xCord, float yCord) : playerPosition(defaultChunk)
{
    this->setHealthPoints(5);
    this->setPosition(xCord, yCord);
    this->currentSpriteSheet = movingDownSprite;
    this->frameRec = {0.0f, 0.0f, (float)this->currentSpriteSheet.width, (float)this->currentSpriteSheet.height};
    ;
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

void Super::getPlayerPosition(MapChunk &actualPosition, float frameTime)
{
    this->playerPosition = actualPosition;
    this->frameTime = frameTime;
}
