#ifndef STACK_H
#define STACK_H

#include "Node.hpp"
#include "LinkedList.h"


template<typename T>
class Stack{
    private:
        LinkedList<T> elements;
    public:
        Stack();

        void push(T data);
        
        B_Node<T>* pop();

        int size();
}

#include "Stack.cpp"

#endif // STACK_H