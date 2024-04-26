#ifndef DLINKEDLIST_H
#define DLINKEDLIST_H

#include "Node.hpp"
#include <stdexcept>

/// @brief C++ implementation of a linked list of nodes with forward and backward pointers
/// @tparam T: data type name
template<typename T>
class DoubleLinkedList{
    public: // Atributes
        int size;
    private:
        B_Node<T>* head;
        B_Node<T>* tail;
    public: // Methods

        /// @brief Default constructor
        DoubleLinkedList(): size(0), head(nullptr), tail(nullptr) {};

        /// @brief Insert a new element at the head of the list 
        /// @param data: value to be added into a node
        void insertAtFront(T data);

        /// @brief Insert a new element at the tail of the list
        /// @param data: value to be added into a node
        void insertAtBack(T data);

        /// @brief Remove an element from the list
        /// @param index: postion of the value to remove
        void remove(int index);

        /// @brief Remove an element from the list
        /// @param search_value: data contained in the node to remove
        void remove(T search_value);

        /// @brief Get a reference to a node based on its position
        /// @param index: position of the node
        /// @return Pointer to the node
        B_Node<T>* get(int index);

        /// @brief Find the data of a node from the list
        /// @param index: position of the element
        /// @return Data from the node
        T& find(int index);
}

#include "DoubleLinkedList.cpp"

#endif // DLINKEDLIST_H