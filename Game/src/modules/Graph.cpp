#include "Graph.h"

template<typename T>
Graph<T>::Graph(){
    this->origin = nullptr;
};

template<typename T>
Graph<T>::~Graph(){
    this->clear();
}

template<typename T>
void Graph<T>::add(T data){
    G_Node<T>* new_node = new G_Node<T>(data);
    if (!this->check_existence(new_node)){
        this->graph_nodes.push_back(new_node);
        if (this->origin == nullptr){
            this->origin = new_node;
        }
    }
};

template<typename T>
void Graph<T>::makeConnection(int _first, int _second, bool both_ways, tuple<int, int> weights){
    G_Node<T>* node1 = this->graph_nodes[_first];
    G_Node<T>* node2 = this->graph_nodes[_second];

    node1->addNode(node2, get<0>(weights));
    if (both_ways){
        node2->addNode(node2, get<1>(weights));
    }
};

template<typename T>
void Graph<T>::remove(int _pos){
    G_Node<T>* rm_node = this->graph_nodes[_pos];
    vector< G_Node<T>* > new_graph_nodes;
    // --------------- {Look for all occurrences of the specified node and remove them} --------------- //
    for (int i = 0; i<this->graph_nodes.size(); i++){
        if ( i != _pos){
            G_Node<T>* node = this->graph_nodes[i];

            for (int j = 0; j<node->total_connected; i++){
                if (get<0>(node->connections[j]) == rm_node){
                    node->removeNode(j);
                    break;
                }
            }

            new_graph_nodes.push_back(node);
        }
    }
    // --------------- {Set the graph_nodes without the removed node} --------------- //
    this->graph_nodes = new_graph_nodes;
};

template<typename T>
void Graph<T>::removeConnection(int _first, int _second){
    G_Node<T>* node1 = this->graph_nodes[_first];
    G_Node<T>* node2 = this->graph_nodes[_second];
    for (int i = 0; i<node1->total_connected(); i++){
        if (get<0>(node1->getNode(i) == node2)){
            node1->removeNode(i);
            break;
        }
    }
};

template<typename T>
G_Node<T>* Graph<T>::getNode(int index){
    return this->graph_nodes[index];
};

template<typename T>
int Graph<T>::size(){
    return this->graph_nodes.size();
};

template<typename T>
void Graph<T>::clear(){
    G_Node<T>* node = nullptr;
    for (int i = 0; i < this->graph_nodes.size(); i++){
        node = this->graph_nodes[i];
        delete node;
    }
    this->graph_nodes.clear();
}

template<typename T>
bool Graph<T>::check_existence(G_Node<T>* node){
    for (int i = 0; i<this->graph_nodes.size(); i++){
        if (this->graph_nodes[i] == node){
            return true;
        }
    }
    return false;
};
