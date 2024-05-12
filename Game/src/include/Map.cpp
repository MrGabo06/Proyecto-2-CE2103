#include "Map.h"

#include <vector>

Map2D::Map2D(){
    this->height = 0.f, this->width = 0.f;
    this->grid_size[0] = 0, this->grid_size[1] = 0;
}

Map2D::Map2D(Level level_to_load, float* chunk_size){
    switch (level_to_load){
        case first:
            this->file_asset += "/level1.txt";
            break;

        case second:
            this->file_asset += "/level2.txt";
            break;

        case third:
            this->file_asset += "/level3.txt";
            break;

        case fourth:
            this->file_asset += "/level4.txt";
            break;

        case fifth:
            this->file_asset += "/level5.txt";
            break;
    }
    this->width = chunk_size[0];
    this->height = chunk_size[1];
}

void Map2D::generate(){
    std::vector < std::vector<char> > layout;

    fstream file(this->file_asset);
    if (!file.is_open()){
        throw std::runtime_error("Coded map data file was not found");
    }
    // [READ CHARS FROM FILE ]
    string line_buffer;
    while (getline(file, line_buffer)){
        vector <char> line;
        for (char c : line_buffer){
            if (c != ' '){
                line.push_back(c);
            }
        }
        layout.push_back(line);
    }
    // [ SET MAP2D PROPERTIES ]
    this->grid_size[0] = layout.size();
    this->grid_size[1] = layout[0].size();
        this->width *= grid_size[1];
        this->height *= grid_size[1];
    // [ GENERATE CHUNKS ]
    float positions[2] = {0.f, 0.f};
    float chunk_dimensions[2] = { this->width/this->grid_size[1], this->height/this->grid_size[1]};
    for ( int i = 0; i<layout.size(); i++){
        for (int j = 0; j<layout[i].size(); j++){
            int coords[2] = {i,j};
            MapChunk chunk(layout[i][j], positions[0], positions[1], chunk_dimensions, coords);
            this->grid.add(chunk);
            positions[0] += chunk_dimensions[0];
        }
        positions[1] += chunk_dimensions[1];
        positions[0] = 0.f;
    }
    // [ GENERATE GRAPH <CHUNKS> CONNECTIONS ]
    this->load_boundaries();
}

void Map2D::regenerate(Level new_level, float* chunk_size){
    // [ CLEAR THE GRAPH ]
    this->grid.clear();
    // [ SET THE NEW FILE TO LOAD]
    this->file_asset = "Game/src/resources/map_assets";
    switch (new_level){
        case first:
            this->file_asset += "/level1.txt";
            break;

        case second:
            this->file_asset += "/level2.txt";
            break;

        case third:
            this->file_asset += "/level3.txt";
            break;

        case fourth:
            this->file_asset += "/level4.txt";
            break;

        case fifth:
            this->file_asset += "/level5.txt";
            break;
    }
    this->width = chunk_size[0];
    this->height = chunk_size[1];
    // [ LOAD THE CHUNKS+CONNECTIONS ]
    this->generate();
}

void Map2D::load_boundaries(){
    // [ CREATE GRAPH <CHUNKS> CONNECTIONS ]
    int row_gap = this->grid.size()/this->grid_size[0];
    int i = 0;
    for (int j = 0; j<this->grid.size(); j++){
        MapChunk chunk = this->grid.getNode(j)->data;
        int weight = this->chunk_output(chunk);
        if ( j > 0 && j < this->grid.size()){
            // { Horizontal connections }
            this->grid.makeConnection(j, j+1, false, make_tuple(weight, 0));
            this->grid.makeConnection(j, j-1, false, make_tuple(weight, 0));
            // { Vertical connections }
            this->grid.makeConnection(j, j + (i+1)*row_gap, false , make_tuple(weight, 0));
            if ( i > 0){
                this->grid.makeConnection(j, j + (i-1)*row_gap, false , make_tuple(weight, 0));
            }
        } else if ( j == 0){
            // { Horizontal connections }
            this->grid.makeConnection(j, j+1, false, make_tuple(weight, weight));
            // { Vertical connections }
            this->grid.makeConnection(j, j + (i+1)*row_gap, false, make_tuple(weight, 0));
        } else if ( j == this->grid.size()-1){
            // { Horizontal connections }
            this->grid.makeConnection(j, j-1, false, make_tuple(weight, weight));
            // { Vertical connections }
            this->grid.makeConnection(j, j + (i-1)*row_gap, false, make_tuple(weight, 0));
        }
        if ((j+1)%4 == 0){
            i++;
        }
    }
}

int Map2D::chunk_output(MapChunk chunk){
    int travel_time = 0;
    switch (chunk.chunk_type){
        case terrain:
            travel_time = 100;
            break;
        case wall:
            travel_time = 0;
            break;
        case trap:
            travel_time = 50;
            break;
        case safe:
            travel_time = 100;
            break;
        case fake:
            travel_time = 100;
            break;
        case cloaked:
            travel_time = 25;
            break;
        case gate:
            travel_time = 100;
            break;
    }
    return travel_time;
}

MapChunk& Map2D::get(int i, int j){
    if (i > this->grid_size[0] || i < 0){
        throw std::out_of_range("i value is out of range");
    }
    if (j > this->grid_size[1] || j < 0){
        throw std::out_of_range("j value is out of range");
    }
    int row_gap = this->grid.size()/this->grid_size[0];
    int selection = j + i*row_gap;
    G_Node<MapChunk>* node = this->grid.getNode(selection);
    return node->data;
}

void Map2D::locate_at(Entity* entity, int i, int j, bool change_position){
    // [ NODE <CHUNK> RETRIEVAL ]
    if (i > this->grid_size[0] || i < 0){
        throw std::out_of_range("i value is out of range");
    }
    if (j > this->grid_size[1] || j < 0){
        throw std::out_of_range("j value is out of range");
    }
    int row_gap = this->grid.size()/this->grid_size[0];
    int selection = j + i*row_gap;
    G_Node<MapChunk>* node = this->grid.getNode(selection);
    // [ SET THE LOCATION FOR THE ENTITY]
    entity->setLocation(node, change_position);
}