#include "MapChunk.h"

MapChunk::MapChunk(){
    this->size[0] = 0.f, this->size[1] = 0.f;
    this->position.x = 0.f;
    this->position.y = 0.f;
    this->chunk_type = ChunkType::obstacle;
}

MapChunk::MapChunk(char type, float x, float y, float* _size){
    string assets_path = "Game/src/resources/map_assets";
    if (type == 'x') {
        this->chunk_type = ChunkType::obstacle;
        assets_path += "/chunk3.png";
        Image image = LoadImage(assets_path.c_str());
        this->texture = LoadTextureFromImage(image);
    } else if (type == '.'){
        this->chunk_type = ChunkType::traversable;
        assets_path += "/chunk1.png";
        Image image = LoadImage(assets_path.c_str());
        this->texture = LoadTextureFromImage(image);
    } else if (type == '_') {
        this->chunk_type = ChunkType::slow;
        assets_path += "/chunk2.png";
        Image image = LoadImage(assets_path.c_str());
        this->texture = LoadTextureFromImage(image);
    }
    this->size[0] = _size[0];
    this->size[1] = _size[1];
    this->position.x = x;
    this->position.y = y;
}

Vector2 MapChunk::center(){
    Vector2 result;
        result.x = this->position.x + (this->size[0]/2);
        result.y = this->position.y + (this->size[1]/2);
    return result;
}