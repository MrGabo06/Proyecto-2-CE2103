#ifndef MAP_H
#define MAP_H

#include "MapChunk.h"
#include "../modules/Graph.h"

#include <stdexcept>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

enum Level {
    first,
    second,
    third,
    fourth,
    fifth
};

/// @brief Class for creating a two dimensional map with matrix like grid of chunk assets
class Map2D{
    private: // Atributes
        Graph<MapChunk> grid;
        string file_asset = "Game/src/resources/map_assets";
    public:
        float width;
        float height;
        int grid_size[2] = {0 , 0};

    public: // Methods

        /// @brief Default constructor
        /// @param level_to_load: initial level to load its asset files
        /// @param chunk_size: width and length size for an individual chunk
        Map2D(Level level_to_load, float* chunk_size);

        /// @brief Loads the assets into memory
        void generate();
        
        /// @brief Loads a new set of chunks to memory
        /// @param new_level: level to load its asset files
        /// @param chunk_size: width and length size for an individual chunk (Leave at 0 if chunks must remain the same)
        void regenerate(Level new_level, float* chunk_size);

        /// @brief Get a chunk from the grid
        /// @param i: row
        /// @param j: column
        /// @return MapChunk element
        MapChunk& get(int i, int j);
};

#endif // MAP_H