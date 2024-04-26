#ifndef QUEUE_H
#define QUEUE_H

#include "Node.hpp"
#include "DoubleLinkedList.h"

template<typename T>
class Queue{
   private:
        DoubleLinkedList<T> elements;
    public:
        Queue();

        void enqueue(T data);

        B_Node<T>* dequeue(T data);

        B_Node<T>* getNode(int index);

        T& get(int index);

        int size();
}

#include "Queue.cpp"

#endif // QUEUE_H