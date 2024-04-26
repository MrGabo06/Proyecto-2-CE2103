#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Node.hpp"

/// @brief C++ implementation of Linked List data structure
/// @tparam T: data type name 
template <typename T>
class LinkedList {
    private: // Atributes
        int _size;
        B_Node<T>* head;
    public: // Methods
        /// @brief Default constructor for the list
        LinkedList(): size(0), head(nullptr){};

        /// @brief Inserts a new value into the front of the list (which means the oldest nodes are at the end)
        /// @param data: value to insert into a new node
        void insert(T data);
        
        /// @brief Removes and deallocate the data of a specified indexed node from the list
        /// @param index: position to remove
        void remove(int index);

        /// @brief Retrieves a reference to a node from the list
        /// @param index: position of the node
        /// @return Pointer to the node
        B_Node<T>* getNode(int index);

        /// @brief Retrieves the data contained in a node from the list
        /// @param index: position of the node to find
        /// @return value contained in the node
        T get(int index);

        /// @brief Retrieves the data contained in a node from the list
        /// @param index: position of the node to find
        /// @return value contained in the node
        T operator[](int index);
};

#include "LinkedList.cpp"

#endif // LINKEDLIST_H
