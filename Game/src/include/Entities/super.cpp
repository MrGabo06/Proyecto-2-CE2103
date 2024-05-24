#include "super.h"
#include <iostream>
#include <random>

MapChunk Super::defaultChunk = MapChunk::defaultMapChunk();
Super::Super() : playerPosition(defaultChunk)
{
    this->setPosition(0, 0);
    this->currentSpriteSheet = movingDownSprite;
}

Super::Super(int xCord, int yCord, int skill_rates[]) : playerPosition(defaultChunk)
{
    // [ INITIALIZE THE ENTITY ]
    this->setPosition(0.f, 0.f);
    this->graphX = xCord;
    this->graphY = yCord;
    this->currentSpriteSheet = movingDownSprite;
    this->frameRec = {0.0f, 0.0f, (float)this->currentSpriteSheet.width, (float)this->currentSpriteSheet.height};
    this->setProperties(skill_rates);
}

void Super::getPlayerPosition(MapChunk &actualPosition, float frameTime)
{
    this->playerPosition = actualPosition;
    this->frameTime = frameTime;
}

void Super::shift(float frame_time, int64_t time_stamp)
{
    std::random_device rd; // Objeto para obtener una semilla aleatoria
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 6); // Generador de números aleatorios Mersenne Twister
    this->movePattern(dis(gen));
    if (this->bulletList.getSize() < 3)
    {
        this->bullet = new Bullet(this->getPosition().x, this->getPosition().y);
        this->bullet->shoot(this->playerPosition, this->frameTime);
        bulletList.insert(this->bullet);
    }
}

void Super::setProperties(int scaling[])
{
    this->attributes.cooldown = 4;

    // 1.
    this->attributes.damage[0] = scaling[0];
    this->attributes.damage[1] = (scaling[0] * MAX_DAMAGE.super) / 10;
    if (this->attributes.damage[1] == 0)
    {
        this->attributes.damage[1] = 1;
    }

    // 2.
    this->attributes.distance[0] = scaling[1];
    this->attributes.distance[1] = (scaling[1] * MAX_DISTANCE.super) / 10;
    if (this->attributes.distance[1] == 0)
    {
        this->attributes.distance[1] = 1;
    }

    // 3.
    this->attributes.health[0] = scaling[2];
    this->attributes.health[1] = (scaling[2] * MAX_HEALTH.super) / 10;
    if (this->attributes.health[1] == 0)
    {
        this->attributes.health[1] = 1;
    }
    this->healthPoints = this->attributes.health[1];

    // 4.
    this->attributes.range[0] = scaling[3];
    this->attributes.range[1] = (scaling[3] * MAX_RANGE.super) / 10;
    if (this->attributes.range[1] == 0)
    {
        this->attributes.range[1] = 1;
    }

    // 5.
    this->attributes.route_size[0] = scaling[4];
    this->attributes.route_size[1] = (scaling[4] * MAX_ROUTE_SIZE.super) / 10;
    if (this->attributes.route_size[1] == 0)
    {
        this->attributes.route_size[1] = 1;
    }

    // 6.
    this->attributes.speed[0] = (float)scaling[5];
    this->attributes.speed[1] = (scaling[0] * MAX_SPEED.super) / 10;
    if (this->attributes.speed[1] == 0)
    {
        this->attributes.speed[1] = 1.0;
    }
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
