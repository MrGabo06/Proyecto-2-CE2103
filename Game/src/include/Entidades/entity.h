#ifndef ENTITY_H
#define ENTITY_H

#include <raylib.h>

#include "../modules/Node.hpp"
#include "MapChunk.h"

class MapChunk;

#define entityVerticalSpeed 200.0f
#define entityHorizontalSpeed 200.0f

/// @brief Generic class for game objects
class Entity{
private: // Attributes
    Vector2 position;
    int healthPoints = 0;
    G_Node<MapChunk>* location;
public:
    const char mvUp = 'U';
    const char mvDown = 'D';
    const char mvLeft = 'L';
    const char mvRight = 'R';
public: //Methods
    void move(float frameTime, const char dir);

    Vector2 getPosition();

    void setHealthPoints(int newHp);

    void setPosition(float xCords, float yCords);

    void setLocation(G_Node<MapChunk>* map_chunk);
};

#endif // ENTITY_H