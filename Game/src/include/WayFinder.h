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
        /// @brief Default constructor
        WayFinder();

        /// @brief A* algorithm for finding the fastest route from one point to another
        /// @param start: reference to start location
        /// @param goal: reference to finishing location
        /// @return Stack collection of the nodes to follow
        stack<G_Node<MapChunk>*> search(G_Node<MapChunk>* start, G_Node<MapChunk>* goal);

        /// @brief Backtrack algorithm for tracing back from A to B
        /// @param pointA: reference to current location
        /// @param pointB: reference to desired end location
        /// @param route: current order of nodes
        /// @return Vector of the route that leads A to B
        vector<G_Node<MapChunk>*> backtrack(G_Node<MapChunk>* pointA, G_Node<MapChunk>* pointB, vector<G_Node<MapChunk>*> route);
        
};


#endif