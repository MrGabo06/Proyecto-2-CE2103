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
            // List pointers fixing
            if ( index == 0){
                this->head = current->getNext();
            } else if (index == this->size-1){
                this->tail = current->getPrev();
            }
            // Node connection fixing
            if (current->getPrev() != nullptr){
                current->getPrev()->setNext(current->getNext());
            }
            if (current->getNext() != nullptr){
                current->getNext()->setPrev(current->getPrev());
            }

            // Delete the node
            delete current;
            this->size--;
            break;
        }
        current = current->getNext();
        counter++;
    }
}

template<typename T>
void DoubleLinkedList<T>::find_remove(T search_value){
    B_Node<T>* current = this->head;
    int counter = 0;
    while (current != nullptr){
        if (current->data == search_value){
            // List pointers fixing
            if ( counter == 0){
                this->head = current->getNext();
            } else if (counter == this->size-1){
                this->tail = current->getPrev();
            }
            // Node connection fixing
            if (current->getPrev() != nullptr){
                current->getPrev()->setNext(current->getNext());
            }
            if (current->getNext() != nullptr){
                current->getNext()->setPrev(current->getPrev());
            }

            // Delete the node
            delete current;
            this->size--;
            break;
        }
        current = current->getNext();
        counter++;
    }
}

template<typename T>
B_Node<T>* DoubleLinkedList<T>::find(int index){
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
T& DoubleLinkedList<T>::get(int index){
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