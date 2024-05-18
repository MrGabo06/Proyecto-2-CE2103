#include "WayFinder.h"

#include <math.h>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>


// [ Helper methods for algorithm ]

float heuristic(const MapChunk& a, const MapChunk& b){
    return std::sqrt(std::pow(a.position.x - b.position.x,2)+ std::pow(a.position.y-b.position.y,2));
}

// Comparator for priority queue
struct Compare {
    bool operator()(const std::pair<float, G_Node<MapChunk>*>& a, const std::pair<float, G_Node<MapChunk>*>& b) const {
        return a.first > b.first;
    }
};

// Function to reconstruct the path
std::stack<G_Node<MapChunk>*> reconstruct_path(std::unordered_map<G_Node<MapChunk>*, G_Node<MapChunk>*>& cameFrom, G_Node<MapChunk>* current) {
    std::stack<G_Node<MapChunk>*> total_path;
    while (cameFrom.find(current) != cameFrom.end()) {
        total_path.push(current);
        current = cameFrom[current];
    }
    total_path.push(current); // Add the start node
    return total_path;
}

// [ Class methods ]

WayFinder::WayFinder(){

}

stack<G_Node<MapChunk>*> WayFinder::search(G_Node<MapChunk>* start, G_Node<MapChunk>* goal){
    std::priority_queue<std::pair<float, G_Node<MapChunk>*>, std::vector<std::pair<float, G_Node<MapChunk>*>>, Compare> openSet;
    std::unordered_map<G_Node<MapChunk>*, float> gScore;
    std::unordered_map<G_Node<MapChunk>*, float> fScore;
    std::unordered_map<G_Node<MapChunk>*, G_Node<MapChunk>*> cameFrom;
    std::unordered_set<G_Node<MapChunk>*> openSetNodes;

    openSet.emplace(0.0f, start);
    openSetNodes.insert(start);
    gScore[start] = 0.0f;
    fScore[start] = heuristic(start->data, goal->data);

    while (!openSet.empty()) {
        G_Node<MapChunk>* current = openSet.top().second;
        openSet.pop();
        openSetNodes.erase(current);

        if (current->data == goal->data) {
            return reconstruct_path(cameFrom, current);
        }

        for (auto& neighborData : current->connections) {
            auto& neighbor = get<0>(neighborData);
            float weight = (float)get<1>(neighborData);
            float tentative_gScore = gScore[current] + weight;

            if (tentative_gScore < gScore[neighbor]) {
                cameFrom[neighbor] = current;
                gScore[neighbor] = tentative_gScore;
                fScore[neighbor] = tentative_gScore + heuristic(neighbor->data, goal->data);

                if (openSetNodes.find(neighbor) == openSetNodes.end()) {
                    openSet.emplace(fScore[neighbor], neighbor);
                    openSetNodes.insert(neighbor);
                }
            }
        }
    }

    return {}; // Return empty stack if no path is found
}

vector<G_Node<MapChunk>*> WayFinder::backtrack(G_Node<MapChunk>* pointA, G_Node<MapChunk>* pointB, vector<G_Node<MapChunk>*> route){
    if (pointA->data == pointB->data){
        return route; // Return the current saved route to point
    } else {
        for ( auto neighbor : pointA->connections){
            auto node = get<0>(neighbor);
            std::cout << node->data.coordinates[0] << "+" << node->data.coordinates[1] << std::endl;
            bool repeated = false;
            for ( auto known : route){
                if (known->data == node->data){
                    repeated = true;
                    break;
                }
            }
            if (!repeated && node->data.chunk_type != ChunkType::wall && node->data.chunk_type != ChunkType::fake){
                if ( node->data == pointB->data){
                    route.push_back(node);
                    return route;
                } else {
                    route.push_back(node);
                    return backtrack(node, pointB, route);
                }
            }
        }
    }
}