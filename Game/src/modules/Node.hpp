#ifndef NODE_H
#define NODE_H

#include <vector>
#include <stdexcept>
#include <tuple>

/// @brief C++ implementation of a simple (binary) node useful for linear data structures and binary trees
/// @tparam T: data type name for the node
template<typename T>
class B_Node {
    public: // Attributes
        T data;
    private:
        B_Node<T>* R;
        B_Node<T>* L;
    public: // Methods
        
        /// @brief Default constructor for a binary node
        /// @param value: data to insert into node
        B_Node(T value){
            this->data = value;
            this->R = nullptr;
            this->L = nullptr;
        }

        /// @brief Add a reference to another node as the right child of this node
        /// @param node: pointer to the other node
        void setRight(B_Node<T>* node){
            this->R = node;
        }
        /// @brief Add a reference to another node as the left child of this node
        /// @param node: pointer to the other node
        void setLeft(B_Node<T>* node){
            this->L = node;
        }

        /// @brief Get the reference to the right child node
        /// @return Pointer to right child node in memory
        B_Node<T>* getRight(){
            return this->R;
        }
        /// @brief Get the reference to the left child node
        /// @return Pointer to left child node in memory
        B_Node<T>* getLeft(){
            return this->L;
        }

        /// @brief Add a reference to another node as the next of this node
        /// @param node: pointer to the other node
        void setNext(B_Node<T>* node){
            this->R = node;
        }
        /// @brief Add a reference to another node as the previous of this node
        /// @param node: pointer to the other node
        void setPrev(B_Node<T>* node){
            this->L = node;
        }

        /// @brief Get the reference to the next node
        /// @return Pointer to next node in memory
        B_Node<T>* getNext(){
            return this->R;
        }
        /// @brief Get the reference to the previous node
        /// @return Pointer to previous node in memory
        B_Node<T>* getPrev(){
            return this->L;
        }
        /// @brief Destructor method
        ~B_Node(){

        }
};

/// @brief C++ implementation of a n-ary node for hierarchical data structures with N-child nodes
/// @tparam T: data type name for the node
template<typename T>
class N_Node {
    public: // Attributes
        T data;
        N_Node<T>* parent;
    private:
        std::vector< N_Node<T>* > children; 
    public: // Methods

        /// @brief Default constructor for a n-ary node
        /// @param value: data to insert in node
        N_Node(T value){
            this->data = value;
            this->parent = nullptr;
        }

        /// @brief Adds a new child to this node(as the parent)
        /// @param _child: pointer to another node
        void addChild(N_Node<T>* _child){
            if (_child != nullptr){
                this->children.push_back(_child);
            }
        }

        /// @brief Removes a child node from the list of children
        /// @param _which: number of child to delete (from 1 to n);
        void removeChild(int _which){
            if (this->children.size() == 1){
                N_Node<T>* child = this->children.operator[](_which-1);
                this->children.pop_back();
                delete child;

            } else if (this->children.size() > 1){
                // Swap nodes references
                N_Node<T>* swapped = this->children.operator[](_which-1);
                this->children.operator[](_which-1) = this->children.operator[](this->totalChildren()-1);
                this->children.operator[](this->totalChildren()-1) = swapped;

                // Remove the node reference and deallocate
                this->children.pop_back();
                delete swapped;
            }
        }
        /// @brief Retrieves a reference to a child node
        /// @param _which: number of child(from 1 to n);
        /// @return Pointer to the specified child node
        N_Node<T>* getChild(int _which){
            if (this->children.size() > 0){
                return this->children.operator[](_which-1);
            }
            return nullptr;
        }

        /// @brief Get the amount of children nodes
        /// @return Number of children
        const int totalChildren(){
            return this->children.size();
        }

        /// @brief Destructor method
        ~N_Node(){

        }
};

/// @brief C++ implementation of a weighted graph node (the weight of connections is 0 by default)
/// @tparam T: data type name for the node
template<typename T>
class G_Node {
    public: // Attributes
        T data;
    private:
        std::vector< std::tuple< G_Node<T>*, int> > nodes; 
    public: // Methods

        /// @brief Default constructor for a graph node
        /// @param value: data to insert in node
        G_Node(T value){
            this->data = value;
        }

        /// @brief Adds a node connection from this node to other( with weight 0)
        /// @param _other: reference to other node
        void addNode(G_Node<T>* _other){
            this->addNode(_other, 0);
        }
        
        /// @brief Adds a node connection from this node to other
        /// @param _other: reference to other node
        /// @param _weight: value of the weight of the connection of the two nodes
        void addNode(G_Node<T>* _other, int weight){
            std::tuple< G_Node<T>*, int > connection = std::make_tuple(_other, weight);
            this->nodes.push_back(connection);
        }

        /// @brief Remove a node connection
        /// @param index: position of a node connection
        void removeNode(int index){
            if (index < 0 || index >= this->nodes.size() ){
                throw std::out_of_range("Index out of range");
            }
            if (index == 0){
                std::tuple< G_Node<T>*, int> connection = this->nodes.operator[](index);
                G_Node<T>* ref = std::get<0>(connection);
                this->nodes.pop_back();
                delete ref;
            } else if (index > 0){
                // Swapped the specified element with the last 
                std::tuple< G_Node<T>*, int> connection = this->nodes.operator[](index);
                G_Node<T>* ref = std::get<0>(connection);
                this->nodes.operator[](index) = this->nodes.operator[](this->nodes.size()-1);
                this->nodes.operator[](this->nodes.size()-1) = connection;

                // Remove the 'changed' last element and deallocate the node pointer
                this->nodes.pop_back();
                delete ref;
            }
        }

        /// @brief Retrieves the reference to a connected node
        /// @param index: position of a node connection
        /// @return pointer to connected node
        G_Node<T>* getNode(int index){
            if (index < 0 || index >= this->nodes.size() ){
                throw std::out_of_range("Index out of range");
            }
            std::tuple< G_Node<T>*, int > connection = this->nodes.operator[](index);
            return std::get<0>(connection);
        }
        /// @brief Retrieves the reference of a node connection and its weight
        /// @param index: position of a node connection
        /// @return tuple with pointer to connected node and integer value of weight
        std::tuple< G_Node<T>*, int > getNode_W(int index){
            if (index < 0 || index >= this->nodes.size() ){
                throw std::out_of_range("Index out of range");
            }
            return this->nodes.operator[](index);
        }

        /// @brief Get the number of current connections
        /// @return integer value of the amount of connections
        const int total_connected(){
            return this->nodes.size();
        }

        /// @brief Destructor method
        ~G_Node(){

        }
    private:
        bool operator==(G_Node<T>* _other){
            if (this->data == _other->data){
                return true;
            }
            return false;
        }
};


#endif // NODE_H