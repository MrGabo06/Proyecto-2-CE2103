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

void Bullet::shoot(MapChunk playerPosition, float frameTime)
{
    this->moveTo(playerPosition, frameTime);
}
