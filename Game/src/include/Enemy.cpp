#include "Enemy.h"

void Enemy::moveTo(MapChunk &newMapChunk, float frameTime){
    if (this->getPosition().x < newMapChunk.center().x -20.0f){
        this->move(frameTime,Entity::mvRight);
    }

    if (this->getPosition().x > newMapChunk.center().x + 20.0f){
        this->move(frameTime ,Entity::mvLeft);
    }

    if (this->getPosition().y < newMapChunk.center().y - 20.0f){
        this->move(frameTime ,Entity::mvDown);
    }

    if (this->getPosition().y > newMapChunk.center().y + 20.0f){
        this->move(frameTime, Entity::mvUp);
    }
}
