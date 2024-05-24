#include "Entity.h"
#include "Map.h"

void Entity::move(float frameTime, const char dir)
{
    if (dir == mvUp)
    {
        this->position.y -= entityVerticalSpeed * frameTime * attributes.speed[1];
    }

    if (dir == mvDown)
    {
        this->position.y += entityVerticalSpeed * frameTime * attributes.speed[1];
    }

    if (dir == mvLeft)
    {
        this->position.x -= entityHorizontalSpeed * frameTime * attributes.speed[1];
    }

    if (dir == mvRight)
    {
        this->position.x += entityHorizontalSpeed * frameTime * attributes.speed[1];
    }

    this->graphX = this->getPosition().x / this->cellSize;
    this->graphY = this->getPosition().y / this->cellSize;
}

Attributes Entity::getAttributes(){
    return this->attributes;
}

bool Entity::isSafe(){
    return this->location->data.chunk_type == ChunkType::safe || this->location->data.chunk_type == ChunkType::cloaked;
}

int Entity::getHealth(){
    return healthPoints;
}

int Entity::getShield()
{
    return ShieldPoints;
}

int Entity::getCoins()
{
    return CoinPoints;
}

void Entity::addCoins(int newCoins)
{
    CoinPoints += newCoins;
}

void Entity::addHealthPoints(int newHp){
    healthPoints += newHp;
    LOG(INFO) << "Attack";
}

void Entity::addShieldPoints(int Hp){
    ShieldPoints += Hp;
}

void Entity::setPosition(float xCords, float yCords)
{
    if (xCords != -1.0f)
    {
        position.x = xCords;
    }

    if (yCords != -1.0f)
    {
        position.y = yCords;
    }
}

Vector2 Entity::getPosition()
{
    return position;
}

void Entity::setLocation(G_Node<MapChunk> *map_chunk, bool changePosition)
{
    this->location = map_chunk;
    this->graphX = map_chunk->data.coordinates[1];
    this->graphY = map_chunk->data.coordinates[0];
    if (changePosition)
    {
        this->position = location->data.center();
    }
}

G_Node<MapChunk> *Entity::getLocation()
{
    return this->location;
}
