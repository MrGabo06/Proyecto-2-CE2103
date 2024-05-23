#ifndef QUEUE_H
#define QUEUE_H

#include "Node.hpp"
#include "DoubleLinkedList.h"

/// @brief C++ implementation a basic queue data structure
/// @tparam T: data type name
template<typename T>
class Queue{
    private:
        DoubleLinkedList<T> elements;
    public:
        /// @brief Default constructor
        Queue(){};

        /// @brief Adds a new element at the back of the queue
        /// @param data: value to inserted in the queue
        void enqueue(T data);

        /// @brief Dequeues an element at the front of the queue
        /// @return Element that has left the queue
        B_Node<T> dequeue();

        /// @brief Find any node from the queue
        /// @param index: position of the element
        /// @return Pointer to the node
        B_Node<T>* find(int index);

        /// @brief Get the data of the first element of the queue without removing it
        /// @return Data of the node
        T& peek();

        /// @brief Get the data of an element of the queue
        /// @param index: position of the element
        /// @return Data of the element
        T& get(int index);

        /// @brief Get the current size of the queue
        int size();
};

#include "Queue.cpp"

#endif // QUEUE_H