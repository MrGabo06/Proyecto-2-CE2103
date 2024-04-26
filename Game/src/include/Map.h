#ifndef MAP_H
#define MAP_H

#include "MapChunk.h"
#include "../modules/Graph.h"

#include <stdexcept>
#include <string>

using namespace std;

enum Level {
    first,
    second,
    third,
    fourth,
    fifth
};

class Map{
    private:
        Graph<MapChunk> matrix;
        string map_file;
    public:
        Map(Level level_to_load);

        void Generate_Chunks();



};

#endif // MAP_H