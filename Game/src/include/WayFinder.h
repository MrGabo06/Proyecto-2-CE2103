#ifndef TRACKER_H
#define TRACKER_H

#include <queue>
#include <stack>
#include <vector>
#include "MapChunk.h"
#include "../modules/Node.hpp"

using namespace std;
/// @brief Class for path finding algorithms between graph points
class WayFinder{
    public:
        vector<G_Node<MapChunk>*> obt;
    public:
        /// @brief Default constructor
        WayFinder();

        /// @brief A* algorithm for finding the fastest route from one point to another
        /// @param start: reference to start location
        /// @param goal: reference to finishing location
        /// @return Stack collection of the nodes to follow
        void search(G_Node<MapChunk>* start, G_Node<MapChunk>* goal);

        /// @brief Backtrack algorithm for tracing back from A to B, saves the route in the vector of the instance
        /// @param pointA: reference to current location
        /// @param pointB: reference to desired end location
        void non_weight_search(G_Node<MapChunk>* pointA, G_Node<MapChunk>* pointB);
        
};


#endif