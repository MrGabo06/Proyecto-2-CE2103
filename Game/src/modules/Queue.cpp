#include "Queue.h"

template<typename T>
void Queue<T>::enqueue(T data){
    this->elements.insertAtBack(data);
}

template<typename T>
B_Node<T> Queue<T>::dequeue(){
    B_Node<T> node(this->elements.find(0)->data);
    this->elements.remove(0);
    return node;
}

template<typename T>
B_Node<T>* Queue<T>::find(int index){
    return this->elements.find(index);
}

template<typename T>
T& Queue<T>::get(int index){
    return this->elements.find(index)->data;
}

template<typename T>
int Queue<T>::size(){
    return this->elements.size;
}