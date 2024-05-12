#include "entity.h"

void Entity::move(float frameTime, const char dir){
        if (dir == mvUp)
        {
            this->position.y -= entityVerticalSpeed * frameTime;
        }

        if (dir == mvDown) 
        {
            this->position.y += entityVerticalSpeed * frameTime;
        }

        if (dir == mvLeft)
        {
            this->position.x -= entityHorizontalSpeed * frameTime;
        }

        if (dir == mvRight)
        {
            this->position.x += entityHorizontalSpeed * frameTime;
        }
}

Vector2 Entity::getPosition(){
        return position;
}

void Entity::setHealthPoints(int newHp){
        healthPoints = newHp;
}

void Entity::setPosition(float xCords, float yCords){
        position.x = xCords;
        position.y = yCords;
}

void Entity::setLocation(G_Node<MapChunk>* map_chunk){
    this->location = map_chunk;
    this->position = location->data.center();
}