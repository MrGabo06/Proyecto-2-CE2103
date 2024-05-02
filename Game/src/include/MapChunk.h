#ifndef MAP_CHUNK_H
#define MAP_CHUNK_H

#include <raylib.h>
#include <string>

using namespace std;

enum ChunkType{
    traversable,
    obstacle,
    slow
};

class MapChunk{
    public:
        ChunkType chunk_type;
        Vector2 position;
        float size[2];
        Texture2D texture;
    public:
        MapChunk();
        
        /// @brief Constructor for chunk type
        /// @param type: char value indicating the asset to load
        /// @param x: x coordinates of the chunk
        /// @param y: y coordinates of the chunk
        /// @param size: width and length of the chunk to load 
        MapChunk(char type , float x, float y, float* _size);

        /// @brief Gets the center coordinates of the chunk
        /// @return 
        Vector2 center();
};

#endif // MAP_CHUNK_H