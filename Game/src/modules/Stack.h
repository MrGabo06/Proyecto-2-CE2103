#ifndef STACK_H
#define STACK_H

#include "Node.hpp"
#include "DoubleLinkedList.h"

/// @brief C++ implementation of a stack data structure
/// @tparam T 
template<typename T>
class Stack{
    private:
        DoubleLinkedList<T> elements;
    public:
        /// @brief Default constructor
        Stack();

        /// @brief Adds a new element at the top of the Stack
        /// @param data: data to insert in the Stack
        void push(T data);
        
        /// @brief Removes the element of the Stack
        /// @return Removed node
        B_Node<T> pop();

        /// @brief Get the current size of the Stack
        int size();
}

#include "Stack.cpp"

#endif // STACK_H