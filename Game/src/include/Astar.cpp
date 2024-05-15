#include "Astar.h"
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

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

// A* search function
std::stack<G_Node<MapChunk>*> a_star(Graph<MapChunk>& graph, G_Node<MapChunk>* start, G_Node<MapChunk>* goal) {
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

        if (current == goal) {
            return reconstruct_path(cameFrom, current);
        }

        for (auto& neighborData : current->connections) {
            auto& neighbor = neighborData.first;
            float weight = neighborData.second;
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
