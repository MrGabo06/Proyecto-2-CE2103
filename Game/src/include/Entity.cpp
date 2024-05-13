#include "Entity.h"
#include "Map.h"

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
    if (xCords != -1.0f) {
        position.x = xCords;
    }
    
    if (yCords != -1.0f) {
        position.y = yCords;
    }
}

void Entity::setLocation(G_Node<MapChunk>* map_chunk, bool changePosition){
    this->location = map_chunk;
    if (changePosition) {
        this->position = location->data.center();    
    }

}
int Entity::getHealth(){
    return healthPoints;
}