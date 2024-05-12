#ifndef MANAGER_H
#define MANAGER_H

#include "Entity.h"
#include "Enemy.h"
#include "wrapper.hpp"

#include <chrono>
#include <thread>
#include <mutex>

using namespace std;

enum Collection {
    enemies,
    statical
}

/// @brief Class that takes care of generating the required entities for the game levels
class Manager {
    private: // Attributes
        std::vector<Enemies> enemies;
        std::vector<Entity> statical;
    public: // Methods
        Manager();

        void add(Entity entity);

        Entity& operator[](Collection vect);

        void evolve();
    private:
        void control();
};

#endif // MANAGER_H