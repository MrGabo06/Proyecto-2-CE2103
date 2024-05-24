#include "LinkedList.h"

template <typename T>
void LinkedList<T>::insert(T data)
{
    B_Node<T> *node = new B_Node<T>(data);
    if (this->head == nullptr)
    {
        this->head = node;
    }
    else
    {
        node->setNext(this->head);
        this->head = node;
    }
    this->_size++;
};

template <typename T>
void LinkedList<T>::remove(int index)
{
    int counter = 0;
    B_Node<T> *current = this->head;
    while (counter <= index)
    {
        if (index == 0)
        {
            this->head = current->getNext();
            delete current;
            this->_size--;
            break;
        }
        if (counter == index - 1)
        {
            current->setNext(current->getNext()->getNext());
            delete current->getNext();
            this->_size--;
            break;
        }
        current = current->getNext();
        counter++;
    }
};

template <typename T>
B_Node<T> *LinkedList<T>::getNode(int index)
{
    int counter = 0;
    B_Node<T> *current = this->head;
    while (counter <= index)
    {
        if (counter == index)
        {
            return current;
        }
        current = current->getNext();
        counter++;
    }
    return nullptr;
};

template <typename T>
T& LinkedList<T>::get(int index){
    if (this->head == nullptr){
        throw std::runtime_error("LINKEDLIST: List is empty");
        LOG(ERROR) << "LinkedList.cpp::get List is empty";
    }
    int counter = 0;
    B_Node<T> *current = this->head;
    while (counter <= index){
        if (counter == index){
           break;
        }
        current = current->getNext();
        counter++;
    }
    return current->data;
};

template <typename T>
T LinkedList<T>::operator[](int index)
{
    return this->get(index);
}
template <typename T>
int LinkedList<T>::getSize()
{
    return this->_size;
};
