#ifndef OBSERVER_H
#define OBSERVER_H

#include "../DoubleLinkedList.h"

class Observer{
    protected: // Attributes
        int id;

    public: // Methods
        Observer(){};

        virtual void update(){};

        bool operator==(Observer* other){
            return this == other;
        }
};

class Observable{
    private: // Attributes
        DoubleLinkedList<Observer*> observers;

    public: // Methods
        Observable(){};

        void addObserver(Observer* observer){
            this->observers.insertAtBack(observer);
        };

        void removeObserver(Observer* observer){
            this->observers.find_remove(observer);
        };

        void notify(){
            B_Node<Observer*>* node = this->observers.find(0);
            while (node != nullptr){
                node->data->update();
                node = node->getNext();
            }
        }
};


#endif