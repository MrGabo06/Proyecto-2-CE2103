#ifndef GRAPH_H
#define GRAPH_H

#include "Node.hpp"

#include <tuple>
#include <vector>
#include <glog/logging.h>

using namespace std;

/// @brief C++ implementation of a graph
/// @tparam T: data type name
template<typename T>
class Graph{
    public: // Attributes
        G_Node<T>* origin;
    private:
        vector < G_Node<T>* > graph_nodes;
    
    public: // Methods
        
        /// @brief Default constructor method for Graph
        Graph();

        /// @brief Destructor method
        ~Graph();

        /// @brief Add a new element to the graph
        /// @param data: value to insert in a new graph node
        void add(T data);

        /// @brief Make a connection between two existing graph elements(nodes)
        /// @param _first: position(index) of the first element
        /// @param _second: position(index) of the second element
        /// @param both_ways: (true) allows linking first with second, and second with first. (false) only links first with second
        /// @param weights: tuple with weights of both connections
        void makeConnection(int _first, int _second, bool both_ways, tuple<int, int> weights);

        /// @brief Removes a node from the graph and all related existent connections
        /// @param _pos: position of the node to remove
        void remove(int _pos);

        /// @brief Removes a connection of between two graph nodes(if the connection exists)
        /// @param _first: node to in which to remove connection
        /// @param _second: connected node to remove
        void removeConnection(int _first, int _second);

        /// @brief Retrieves a reference to a node from the graph
        /// @param index: position of the node of the graph
        /// @return Pointer to a node.
        G_Node<T>* getNode(int index);

        /// @brief Get the size of the graph
        /// @return Value of the size
        int size();

        /// @brief Clears all nodes from the graph
        void clear();
    private:
        /// @brief Verifies if a node already exists in the graph
        /// @param node: node reference to verify if its exists
        /// @return True if node is found and false if node is never found
        bool check_existence(G_Node<T>* node);

};

#include "Graph.cpp"

#endif // DLINKEDLIST_H
