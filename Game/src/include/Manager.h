#ifndef MANAGER_H
#define MANAGER_H

#include "Entity.h"
#include "Enemy.h"
#include "Map.h"
#include "wrapper.hpp"
#include "Entities/player.h"
#include "../modules/RandGenerator.h"

#include <ctime>
#include <chrono>
#include <thread>
#include <mutex>
#include <math.h>


using namespace std;

enum EntGroup
{
    enemies,
    statical
};

enum EntityType
{
    CHOCOBO,
    EYE,
    RAT,
    SPECTER,
    SUPER,
    TREASURE,
    VASE
};

enum Performance {
    veryPoor,
    Poor,
    Average,
    Good,
    veryGood
};

/// @brief Class that takes care of generating the required entities for the game levels
class Manager {
    private: // Attributes
        Generator randomizer;
    // ---- [Collections of entities]
        std::vector<Enemy*> mob_entities;
        std::vector<Entity*> static_entities;

        std::mutex entities_lock;

        bool active_status;
        std::mutex status_lock;
    // ---- [Parameters for entity creation]
        Map2D* origin;

        Performance machine_st = Performance::Average;
        int stats[6] = {4, 4, 4, 4, 4, 4};

    public: // Methods

        /// @brief Default constructor
        Manager();

        /// @brief Constructor for class
        /// @param source: reference to the map where the entities should spawn
        /// @param specters: number of specters to spawn
        /// @param eyes: number of eyes to spawn
        /// @param rats: number of rats to spawn
        /// @param chocobos: number of chocobos to spawn
        /// @param supers: number of supers to spawn
        /// @param treasures: number of treasures to spawn
        /// @param vases: : number of vases to spawn
        Manager(Map2D* source, int specters, int eyes, int rats, int chocobos, int supers, int treasures, int vases);

        /// @brief Adds a new group of entities to the management unit
        /// @param type: entity type to add
        /// @param quantity: amount of new entities to add
        void addEntities(EntityType entity_t, int quantity);

        /// @brief Gets a reference to an Entity managed by this instance
        /// @param group: name of group to access
        /// @param index: position
        /// @return Pointer to an Entity; can be casted to requested type using 'dynamic_cast<...>' or 'static_cast<...>'
        Entity* getEntity(EntGroup group, int index);

        /// @brief Gets the size of the group of entities
        /// @param group: name of group
        int size(EntGroup group);

        /// @brief Kills all entities of held by this instance
        /// @param current_time: sets this time as their lifetime
        void killAll(int64_t current_time);

        /// @brief Analyzes the results of the enemies and generates new behaviors/attributes
        /// @param specters 
        /// @param eyes 
        /// @param rats 
        /// @param chocobos 
        /// @param supers 
        /// @param treasures 
        /// @param vases 
        void evolve(int specters, int eyes, int rats, int chocobos, int supers, int treasures, int vases);
};

#endif // MANAGER_H