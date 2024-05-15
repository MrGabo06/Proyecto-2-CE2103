#pragma once

#include "../modules/Graph.h"
#include "MapChunk.h"
#include <stack>

// Heuristic function
float heuristic(const MapChunk& a, const MapChunk& b);

// A* search function
std::stack<G_Node<MapChunk>*> a_star(Graph<MapChunk>& graph, G_Node<MapChunk>* start, G_Node<MapChunk>* goal);
