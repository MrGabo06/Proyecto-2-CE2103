#include "Stack.h"

template<typename T>
void Stack<T>::push(T data){
    this->elements.insertAtFront(data);
}

template<typename T>
B_Node<T> Stack<T>::pop(){
    B_Node<T> node(this->elements.find(0)->data);
    this->elements.remove(0);
    return node;
}

template<typename T>
T& Stack<T>::peek(){
    return this->elements.get(0);
}

template<typename T>
int Stack<T>::size(){
    return this->elements.size;
}