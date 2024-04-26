#include "Stack.h"

template<typename T>
void Stack<T>::push(T data){
    this->elements.insertAtFront(data);
}

template<typename T>
B_Node<T> Stack<T>::pop(){
    B_Node<T> node(this->elements.find(this->size()-1)->data);
    this->elements.remove(this->size()-1);
    return node;
}

template<typename T>
int Stack<T>::size(){
    return this->elements.size;
}