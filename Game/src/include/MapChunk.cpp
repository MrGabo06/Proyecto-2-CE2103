#include "MapChunk.h"

MapChunk::MapChunk(){
    this->size[0] = 0.f, this->size[1] = 0.f;
    this->coordinates[0] = 0, this->coordinates[1] = 0;
    this->position.x = 0.f;
    this->position.y = 0.f;
    this->chunk_type = ChunkType::terrain;
    this->light = false;
    this->breadcrumb = 0;
    // // RayLib elements
    // Image dark_image = LoadImage("Game/src/resources/map_assets/chunk7.png");
    // this->darkened = LoadTextureFromImage(dark_image);
    // Image light_image = LoadImage("Game/src/resources/map_assets/chunk1.png");
    // this->illuminated = LoadTextureFromImage(light_image);

    // this->texture = illuminated;
}

MapChunk::MapChunk(char type, float x, float y, float *_size, int *coords, bool dark_map){
    const string assets_path = "Game/src/resources/map_assets/";
    if (type == 'x'){
        this->chunk_type = ChunkType::wall;
        Image dark_image = LoadImage((assets_path+"chunk7.png").c_str());
        this->darkened = LoadTextureFromImage(dark_image);
        Image light_image = LoadImage((assets_path+"chunk3.png").c_str());
        this->illuminated = LoadTextureFromImage(light_image);
    } else if (type == '_') {
        this->chunk_type = ChunkType::trap;
        Image dark_image = LoadImage((assets_path+"chunk7.png").c_str());
        this->darkened = LoadTextureFromImage(dark_image);
        Image light_image = LoadImage((assets_path+"chunk4.png").c_str());
        this->illuminated = LoadTextureFromImage(light_image);
    } else if (type == '.'){
        this->chunk_type = ChunkType::terrain;
        Image dark_image = LoadImage((assets_path+"chunk7.png").c_str());
        this->darkened = LoadTextureFromImage(dark_image);
        Image light_image = LoadImage((assets_path+"chunk1.png").c_str());
        this->illuminated = LoadTextureFromImage(light_image);
    } else if (type == 'H') {
        this->chunk_type = ChunkType::gate;
        Image dark_image = LoadImage((assets_path+"chunk7.png").c_str());
        this->darkened = LoadTextureFromImage(dark_image);
        Image light_image = LoadImage((assets_path+"chunk6.png").c_str());
        this->illuminated = LoadTextureFromImage(light_image);
    } else if (type == '~') {
        this->chunk_type = ChunkType::cloaked;
        Image dark_image = LoadImage((assets_path+"chunk7.png").c_str());
        this->darkened = LoadTextureFromImage(dark_image);
        Image light_image = LoadImage((assets_path+"chunk2.png").c_str());
        this->illuminated = LoadTextureFromImage(light_image);
    } else if (type == 'o') {
        this->chunk_type = ChunkType::safe;
        Image dark_image = LoadImage((assets_path+"chunk7.png").c_str());
        this->darkened = LoadTextureFromImage(dark_image);
        Image light_image = LoadImage((assets_path+"chunk5.png").c_str());
        this->illuminated = LoadTextureFromImage(light_image);
    } else if (type == '|') {
        this->chunk_type = ChunkType::fake;
        Image dark_image = LoadImage((assets_path+"chunk7.png").c_str());
        this->darkened = LoadTextureFromImage(dark_image);
        Image light_image = LoadImage((assets_path+"chunk3.png").c_str());
        this->illuminated = LoadTextureFromImage(light_image);
    }
    this->coordinates[0] = coords[0], this->coordinates[1] = coords[1];
    this->size[0] = _size[0];
    this->size[1] = _size[1];
    if (dark_map){
        this->texture = this->darkened;
    } else {
        this->texture = this->illuminated;
    }
    this->position.x = x;
    this->position.y = y;
}

Vector2 MapChunk::center(){
    Vector2 result;
    result.x = this->position.x + (this->size[0] / 2);
    result.y = this->position.y + (this->size[1] / 2);
    return result;
}

bool MapChunk::contains(Entity entity){
    Vector2 coords = entity.getPosition();
    float start_point[] = {this->position.x, this->position.y};
    float end_point[] = {this->position.x + this->size[0], this->position.y + this->size[1]};
    if ((coords.x > start_point[0] && coords.x < end_point[0]) && (coords.y > start_point[1] && coords.y < end_point[1])){
        return true;
    }
    return false;
}

bool MapChunk::operator==(MapChunk other){
    return this->coordinates[0] == other.coordinates[0] && this->coordinates[1] == other.coordinates[1];
}

void MapChunk::lightChunk(){
    this->light = true;
    this->texture = illuminated;
}

void MapChunk::unLightChunk(){
    this->light = false;
    this->texture = darkened;
}
