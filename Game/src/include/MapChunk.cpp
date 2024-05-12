#include "MapChunk.h"

MapChunk::MapChunk(){
    this->size[0] = 0.f, this->size[1] = 0.f;
    this->coordinates[0] = 0, this->coordinates[1] = 0;
    this->position.x = 0.f;
    this->position.y = 0.f;
    this->chunk_type = ChunkType::wall;
}

MapChunk::MapChunk(char type, float x, float y, float* _size, int* coords){
    string assets_path = "Game/src/resources/map_assets";
    if (type == 'x') {
        this->chunk_type = ChunkType::wall;
        assets_path += "/chunk3.png";
        Image image = LoadImage(assets_path.c_str());
        this->texture = LoadTextureFromImage(image);
    } else if (type == '_') {
        this->chunk_type = ChunkType::trap;
        assets_path += "/chunk4.png";
        Image image = LoadImage(assets_path.c_str());
        this->texture = LoadTextureFromImage(image);
    } else if (type == '.'){
        this->chunk_type = ChunkType::terrain;
        assets_path += "/chunk1.png";
        Image image = LoadImage(assets_path.c_str());
        this->texture = LoadTextureFromImage(image);
    } else if ( type == 'H') {
        this->chunk_type = ChunkType::gate;
        assets_path += "/chunk6.png";
        Image image = LoadImage(assets_path.c_str());
        this->texture = LoadTextureFromImage(image);
    } else if ( type == '~') {
        this->chunk_type = ChunkType::cloaked;
        assets_path += "/chunk2.png";
        Image image = LoadImage(assets_path.c_str());
        this->texture = LoadTextureFromImage(image);
    } else if ( type == 'o') {
        this->chunk_type = ChunkType::safe;
        assets_path += "/chunk5.png";
        Image image = LoadImage(assets_path.c_str());
        this->texture = LoadTextureFromImage(image);
    } else if ( type == '|') {
        this->chunk_type = ChunkType::fake;
        assets_path += "/chunk7.png";
        Image image = LoadImage(assets_path.c_str());
        this->texture = LoadTextureFromImage(image);
    }
    this->coordinates[0] = coords[0], this->coordinates[1] = coords[1];
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

bool MapChunk::contains(Entity entity){
    Vector2 coords = entity.getPosition();
    float start_point[] = {this->position.x , this->position.y};
    float end_point[] = {this->position.x + this->size[0], this->position.y + this->size[1]};
    if ( (coords.x > start_point[0] && coords.x < end_point[0]) && ( coords.y > start_point[1] && coords.y < end_point[1])){
        return true;
    }
    return false;
}