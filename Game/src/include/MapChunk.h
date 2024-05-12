#ifndef MAP_CHUNK_H
#define MAP_CHUNK_H

#include "Entity.h"
#include <raylib.h>
#include <string>

class Entity;

using namespace std;

enum ChunkType{
    terrain,
    wall,
    trap,
    safe,
    fake,
    cloaked,
    gate
};

/// @brief Class for building world map chunks
class MapChunk{
public:
    ChunkType chunk_type;
    Vector2 position;
    int coordinates[2];
    float size[2];
    Texture2D texture;
public:
    /// @brief Default constructor
    MapChunk();

    /// @brief Constructor for chunk type
    /// @param type: char value indicating the asset to load
    /// @param x: x coordinates of the chunk
    /// @param y: y coordinates of the chunk
    /// @param size: width and length of the chunk to load 
    MapChunk(char type , float x, float y, float* _size, int* coords);

    /// @brief Gets the x,y central positions of the chunk
    /// @return raylib Vector2 with the position
    Vector2 center();

    /// @brief Verifies if an entity is currently inside the chunk
    /// @param entity: asking entity
    /// @return (true) if entity's x,y position is inside bounds, (false) if entity's x,y position is out of bounds
    bool contains(Entity entity);
};

#endif // MAP_CHUNK_H