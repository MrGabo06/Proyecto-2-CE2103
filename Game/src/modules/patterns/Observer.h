#ifndef OBSERVER_H
#define OBSERVER_H

#include "../DoubleLinkedList.h"
#include "../../include/Entity.h"

class Observer{
    protected: // Attributes
        Entity* detected = nullptr;

    public: // Methods
        Observer(){};

        virtual void update(Entity* target){};

        bool operator==(Observer* other){
            return this == other;
        }
};

class Observable{
    private: // Attributes
        DoubleLinkedList<Observer*> observers;
    protected:
        Entity* detected = nullptr;

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
                node->data->update(this->detected);
                node = node->getNext();
            }
        }
};


#endif