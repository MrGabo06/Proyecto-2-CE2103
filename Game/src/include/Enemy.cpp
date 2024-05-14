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


void Enemy::shift(Map2D* ref){
    B_Node< tuple<int,int> > new_coords = this->route.dequeue();
    ref->locate_at(this, get<0>(new_coords.data), get<1>(new_coords.data), true);
    this->route.enqueue(new_coords.data);
}

void Enemy::randomRoute(){
    this->route.enqueue(make_tuple(random_generator.generateInt(0,4), random_generator.generateInt(0,7)));
    this->route.enqueue(make_tuple(random_generator.generateInt(0,7), random_generator.generateInt(0,4)));
};