#ifndef ENTITY_H
#define ENTITY_H

#include <raylib.h>

#include "../modules/Node.hpp"
#include "../modules/LinkedList.h"
#include "MapChunk.h"

class MapChunk;

#define entityVerticalSpeed 200.0f
#define entityHorizontalSpeed 200.0f

struct Attributes{
    int cooldown;
    int health[2];
    int damage[2];
    int range[2];
    int distance[2];
    int route_size[2];
    float speed[2];
};

/// @brief Generic class for game objects
class Entity{
protected: // Attributes

    // { LOCATION AND POSITION}
    Vector2 position;
    G_Node<MapChunk>* location = nullptr;

    /// { ENTITY ATTRIBUTES }
    Attributes attributes = {2, {0,5}, {0,1}, {0,6}, {0,1}, {0,5}, {0.0, 1.0} };
    int healthPoints = 0;
    int ShieldPoints = 0;

public:
    LinkedList<MapChunk>* breadcrumbs = nullptr;
  
    int cellSize = 59;
    int graphX = 0;
    int graphY = 0;
    Texture2D currentSpriteSheet;

    const char mvUp = 'U';
    const char mvDown = 'D';
    const char mvLeft = 'L';
    const char mvRight = 'R';

    int direction = 0;
    bool isAtacking = false;

public: // Methods
    Entity(){};

    /// @brief Moves the entity to the given direction
    /// @param frameTime: Raylib window frame time
    /// @param dir: Direction the entity will move to
    virtual void move(float frameTime, const char dir);

    /// @brief Modify (add or take) health points
    /// @param newHp: Health points to be added to the current ones
    void addHealthPoints(int newHp);

    /// @brief Give the extra health points to the entity
    /// @param newHp: Health points to be added to the current ones
    void addShieldPoints(int Hp);

    /// @brief Get the entity health points
    /// @return Entity health points
    int getHealth();

    /// @brief Get the entity shield points
    int getShield();

    /// @brief Change the position to a new one
    /// @param xCords: New X position (-1.0f wont change the current)
    /// @param yCords: New Y position (-1.0f wont change the current)
    void setPosition(float xCords, float yCords);

    /// @brief Get entity's position
    /// @return Vector2 object
    Vector2 getPosition();

    /// @brief Changes the location in the graph and the position
    /// @param map_chunk: Pointer to the new map_chunk the entity will be placed in
    /// @param changePosition: True will fix the entity in the center of the map_chunk associated to the graph node
    void setLocation(G_Node<MapChunk>* map_chunk, bool changePosition);

    /// @brief Gets the pointer to map graph node where the entity is standing
    /// @return Pointer to node
    G_Node<MapChunk> *getLocation();

    Attributes getAttributes();
};

#endif // ENTITY_H