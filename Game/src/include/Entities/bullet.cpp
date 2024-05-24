#include "bullet.h"

Bullet::Bullet(){
    this->currentSpriteSheet = movingLeftSprite;
}

Bullet::Bullet(float xCord, float yCord){
	LOG(INFO) << "Bullet instantiated";
    this->setPosition(xCord, yCord);
    this->currentSpriteSheet = movingLeftSprite;
    hit = false;
}

void Bullet::shoot(MapChunk playerPosition, float frameTime){
    this->moveTo(playerPosition, frameTime);
    this->graphX = playerPosition.coordinates[1];
    this->graphY = playerPosition.coordinates[0];
}

void Bullet::deleteBull(float x, float y){
    this->setPosition(x, y);
    // if (dir == 1){
    //     this->setPosition(this->getPosition().x - 0.5f, this->getPosition().y + 0.5f);
    // } else if (dir == 2){
    //     this->setPosition(this->getPosition().x + 0.5f, this->getPosition().y + 0.5f);
    // } else if (dir == 3){
    //     this->setPosition(this->getPosition().x - 0.5f, this->getPosition().y - 0.5f);
    // }
    LOG(INFO) << "Bullet shot";
}
