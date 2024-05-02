#include "Map.h"

#include <vector>

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
    float chunk_dimensions[2] = { this->width/this->grid_size[0], this->height/this->grid_size[0]};
    for ( int i = 0; i<layout.size(); i++){
        for (int j = 0; j<layout[i].size(); j++){
            std::cout << layout[i][j] << std::endl;
            MapChunk chunk(layout[i][j], positions[0], positions[1], chunk_dimensions);
            this->grid.add(chunk);
            positions[0] += chunk_dimensions[0];
        }
        positions[1] += chunk_dimensions[1];
        positions[0] = 0.f;
    }
    // [ CREATE GRAPH <CHUNKS> CONNECTIONS ]
    int row_gap = this->grid.size()/this->grid_size[0];
}

void Map2D::regenerate(Level new_level, float* chunk_size){

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
