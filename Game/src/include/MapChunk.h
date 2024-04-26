#ifndef MAP_CHUNK_H
#define MAP_CHUNK_H

#include <raylib.h>
#include <string>

enum ChunkType{
    traversable,
    obstacle,
    slow
};

class MapChunk{
    public:
        const Texture2D chunk;
        ChunkType chunk_type;
    public:
        MapChunk(char type ,std::string file_path);
};

#endif // MAP_CHUNK_H