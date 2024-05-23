#include "bullet.h"

Bullet::Bullet()
{
    this->currentSpriteSheet = movingLeftSprite;
}

Bullet::Bullet(float xCord, float yCord)
{
    this->setPosition(xCord, yCord);
    this->currentSpriteSheet = movingLeftSprite;
}

void Bullet::shoot(int X, int Y, int dir)
{
    if (dir == 1)
    {
        this->setPosition(this->getPosition().x - 0.5f, this->getPosition().y + 0.5f);
    }
    else if (dir == 2)
    {
        this->setPosition(this->getPosition().x + 0.5f, this->getPosition().y + 0.5f);
    }
    else if (dir == 3)
    {
        this->setPosition(this->getPosition().x - 0.5f, this->getPosition().y - 0.5f);
    }
}
