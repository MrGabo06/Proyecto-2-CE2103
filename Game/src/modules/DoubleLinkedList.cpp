#include "DoubleLinkedList.h"

template<typename T>
void DoubleLinkedList<T>::insertAtFront(T data){
    B_Node<T>* newNode = new B_Node<T>(data);
    if (this->head != nullptr){
        this->head->setPrev(newNode);
        newNode->setNext(this->head);
    } else {
        this->tail = newNode;
    }
    this->head = newNode;
    this->size++;
}

template<typename T>
void DoubleLinkedList<T>::insertAtBack(T data){
    B_Node<T>* newNode = new B_Node<T>(data);
    if (this->tail != nullptr) {
        this->tail->setNext(newNode);
        newNode->setPrev(this->tail);
    } else {
        this->head = newNode;
    }
    this->tail = newNode;
    this->size++;
}

template<typename T>
void DoubleLinkedList<T>::remove(int index){
    if (index >= this->size || index < 0){
        throw std::out_of_range("Index out of range");
    }
    B_Node<T>* current = this->head;
    int counter = 0;
    while (current != nullptr){
        if (counter == index){
            B_Node<T>* temp = current;

            current->getPrev()->setNext(current->getNext());
            current->getNext()->setPrev(current->getPrev());

            delete temp;
            this->size--;
            break;
        }
        current = current->getNext();
        counter++;
    }
}

template<typename T>
void DoubleLinkedList<T>::remove(T search_value){
    B_Node<T>* current = this->head;
    while (current != nullptr){
        if (current->data == search_value){
            B_Node<T>* temp = current;

            current->getPrev()->setNext(current->getNext());
            current->getNext()->setPrev(current->getPrev());

            delete temp;
            this->size--;
            break;
        }
        current = current->getNext();
    }
}

template<typename T>
B_Node<T>* DoubleLinkedList<T>::get(int index){
    if (index >= this->size || index < 0){
        throw std::out_of_range("Index out of range");
    }
    int counter = 0;
    B_Node<T>* current = this->head;
    while (current != nullptr){
        if (counter == index){
            break;
        }
        current = current->getNext();
        counter++;
    }
    return current;
}

template<typename T>
T& DoubleLinkedList<T>::find(int index){
    if (index >= this->size || index < 0){
        throw std::out_of_range("Index out of range");
    }
    int counter = 0;
    B_Node<T>* current = this->head;
    while (current != nullptr){
        if (counter == index){
            break;
        }
        current = current->getNext();
        counter++;
    }
    return current->data;
}