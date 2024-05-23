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
std::vector<G_Node<MapChunk>*> reconstruct_path(std::unordered_map<G_Node<MapChunk>*, G_Node<MapChunk>*>& cameFrom, G_Node<MapChunk>* current) {
    std::vector<G_Node<MapChunk>*> path;
    while (cameFrom.find(current) != cameFrom.end()) {
        path.push_back(current);
        current = cameFrom[current];
    }
    path.push_back(current); // Add the start node
    std::reverse(path.begin(), path.end());
    return path;
}

// [ Class methods ]

WayFinder::WayFinder(){

}

void WayFinder::search(G_Node<MapChunk>* start, G_Node<MapChunk>* goal){
    while (this->obt.size() > 0 ){
        this->obt.pop_back();
    }

    std::priority_queue<std::pair<float, G_Node<MapChunk>*>, std::vector<std::pair<float, G_Node<MapChunk>*>>, Compare> frontier;
    std::unordered_map<G_Node<MapChunk>*, float> cost_so_far;
    std::unordered_map<G_Node<MapChunk>*, G_Node<MapChunk>*> cameFrom;

    frontier.emplace(0.0f, start);
    cost_so_far[start] = 0.0f;

    while (!frontier.empty()) {
        G_Node<MapChunk>* current = frontier.top().second;
        frontier.pop();

        if (current->data == goal->data) {
            this->obt = reconstruct_path(cameFrom, current);
            break;
        }

        for (auto neighborData : current->connections) {
            auto neighbor = get<0>(neighborData);
			// skip walls
            if (neighbor->data.chunk_type == ChunkType::wall)
            	continue;
            	
            float weight = (float)get<1>(neighborData);
            float new_cost = cost_so_far[current] + weight;
            float priority;

            if ((cost_so_far.find(neighbor) == cost_so_far.end()) || (new_cost < cost_so_far[neighbor])) {
                cameFrom[neighbor] = current;
                cost_so_far[neighbor] = new_cost;
                priority = new_cost + heuristic(neighbor->data, goal->data);
                
                /* como el priority_queue de c++ no tiene reprioritize, si el vecino
                ya estaba en la cola, se va a agregar otra vez, entonces se va a revisar
                dos veces. Esto sigue siendo mas barato computacionalmente que reacomodar el
                priority_queue manualmente para cambiarle la prioridad el vecino. O(n) vs O(4) */
                frontier.emplace(priority, neighbor);
            }
        }
    }
}


void back_track(vector<G_Node<MapChunk>*>* output,G_Node<MapChunk> *pointA, G_Node<MapChunk> *pointB,vector<G_Node<MapChunk>*> route, unordered_set<G_Node<MapChunk>*>& visited){
    if (pointA->data == pointB->data){ // Base case: update the route
        *output = route;
    } else { // Recursive case
        for (auto connection : pointA->connections){
            auto node = get<0>(connection);
            if (visited.count(node) == 0 && node->data.chunk_type == ChunkType::terrain ){
                visited.insert(node);
                route.push_back(node);
                back_track(output, node, pointB, route, visited);
            }
        }
    }
}

void WayFinder::non_weight_search(G_Node<MapChunk> *pointA, G_Node<MapChunk> *pointB){
    vector<G_Node<MapChunk>*> route;
    unordered_set<G_Node<MapChunk>*> visited;
    while (this->obt.size() > 0){
        this->obt.pop_back();
    }
    back_track(&this->obt, pointA,pointB,route,visited);
}
