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

void Bullet::shoot()
{
    moveTo(map.get(graphY, graphX), frameTime);
}
