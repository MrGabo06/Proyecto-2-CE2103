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
protected: // Attributes
    Vector2 position;
    int healthPoints = 0;
    G_Node<MapChunk>* location;

public:
    int cellSize = 48;
    int graphX = 0;
    int graphY = 0;
    Texture2D currentSpriteSheet;

    const char mvUp = 'U';
    const char mvDown = 'D';
    const char mvLeft = 'L';
    const char mvRight = 'R';

public: // Methods

    Entity(){};
    
    /// @brief Moves the entity to the given direction
    /// @param frameTime: Raylib window frame time
    /// @param dir: Direction the entity will move to
    virtual void move(float frameTime, const char dir);


    /// @brief Modify (add or take) health points 
    /// @param newHp: Health points to be added to the current ones
    void setHealthPoints(int newHp);

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
    G_Node<MapChunk>* getLocation();

    /// @brief Get the entity health points
    /// @return Entity health points
    int getHealth();
};

#endif // ENTITY_H