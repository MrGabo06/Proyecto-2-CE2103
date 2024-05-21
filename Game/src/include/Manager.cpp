#include "Manager.h"

#include <iostream>

Manager::Manager(){
    this->origin = nullptr;
}

Manager::Manager(Map2D* source, int specters, int eyes, int rats, int chocobos, int supers, int treasures, int vases){
    // [ SET THE ATTRIBUTE SCALING FOR ENEMIES ]
    for (int x = 0; x < 6; x++){
        this->stats[x] = 10;
    }
    // [ ADD ENTITIES TO VECTORS ]
    this->origin = source;
    this->addEntities(EntityType::SPECTER, specters);
    this->addEntities(EntityType::EYE, eyes);
    this->addEntities(EntityType::RAT, rats);
    this->addEntities(EntityType::CHOCOBO, chocobos);
    this->addEntities(EntityType::SUPER, supers);
    this->addEntities(EntityType::TREASURE, treasures);
    this->addEntities(EntityType::VASE, vases);

    // [ START THE CONTROLLER THREAD ]
    this->active_status = true;
    //thread(&Manager::control, this).detach();
}

void Manager::addEntities(EntityType entity_t, int quantity){
    this->entities_lock.lock();
    if ( entity_t == EntityType::TREASURE && entity_t == EntityType::VASE){ // Generate static entities
        Entity* entity = nullptr;
        for (int i = 0; i < quantity; i++){
            // [ CREATE AND SET A NON-CLUTTERING LOCATION FOR ENTITY]
            int location_coords[2] = {randomizer.gen(1,this->origin->grid_size[0]-2), randomizer.gen(1,this->origin->grid_size[1]-2)};
            MapChunk& chunk = this->origin->get(location_coords[0], location_coords[1]);
            while (chunk.chunk_type != ChunkType::terrain){ // { CHECK THE CHUNK IS WALKABLE TERRAIN }
                int offset[] = {randomizer.gen(-1,1), randomizer.gen(-1,1)};
                location_coords[0] += offset[0];
                if (location_coords[0] > this->origin->grid_size[0]-1){
                    location_coords[0] = this->origin->grid_size[0]-2;
                } else if (location_coords[0] < 1){
                    location_coords[0] = 1;
                }
                location_coords[1] += offset[1];
                if (location_coords[1] > this->origin->grid_size[1]-1){
                    location_coords[1] = this->origin->grid_size[1]-2;
                }   else if (location_coords[1] < 1){
                    location_coords[1] = 1;
                }
                chunk = this->origin->get(location_coords[0], location_coords[1]);
            }
            // [ CREATE THE REQUIRED ENTITY ]
            switch (entity_t){
                case VASE:
                    entity = new Vase(0,0);
                    break;
                case TREASURE:
                    entity = new Vase(0,0);
                    break;
            }
            // [ LOCATE THE ENEMY AND GENERATES IT ROUTE ]
            this->origin->locate_at(entity, location_coords[0], location_coords[1], true);
            // [ ADD ENTITY TO LIST ]
            this->static_entities.push_back(entity);
        }
    } else { // Create enemies
        Enemy* enemy = nullptr;
        for (int i = 0; i < quantity; i++) {
            // [ CREATE AND SET A NON-CLUTTERING LOCATION FOR ENTITY]
            int location_coords[2] = {randomizer.gen(1,this->origin->grid_size[0]-2), randomizer.gen(1,this->origin->grid_size[1]-2)};
            std::cout << location_coords[0] << "   " << location_coords[1] << std::endl;
            MapChunk& chunk = this->origin->get(location_coords[0], location_coords[1]);
            while (chunk.chunk_type != ChunkType::terrain){ // { CHECK THE CHUNK IS WALKABLE TERRAIN }
                int offset[] = {randomizer.gen(-1,1), randomizer.gen(-1,1)};
                location_coords[0] += offset[0];
                if (location_coords[0] > this->origin->grid_size[0]-1){
                    location_coords[0] = this->origin->grid_size[0]-2;
                } else if (location_coords[0] < 1){
                    location_coords[0] = 1;
                }
                location_coords[1] += offset[1];
                if (location_coords[1] > this->origin->grid_size[1]-1){
                    location_coords[1] = this->origin->grid_size[1]-2;
                }   else if (location_coords[1] < 1){
                    location_coords[1] = 1;
                }
                std::cout << location_coords[0] << "   " << location_coords[1] << std::endl;
                chunk = this->origin->get(location_coords[0], location_coords[1]);
            }
            // [ CREATE THE REQUIRED ENEMY ]
            switch (entity_t){
                case SPECTER:
                    enemy = new Specter(0,0,this->stats);
                    break;
                case CHOCOBO:
                    enemy = new Chocobo(0,0,this->stats);
                    break;
                case RAT:
                    enemy = new Rat(0,0,this->stats);
                    break;
                case SUPER:
                    enemy = new Super(0,0,this->stats);
                    break;
                case EYE:
                    enemy = new Eye(0,0,this->stats);
                    break;
            }
            // [ LOCATE THE ENEMY AND GENERATES IT ROUTE ]
            this->origin->locate_at(enemy, location_coords[0], location_coords[1], true);
            enemy->generateRoute(this->origin);
            // [ ADD THE ENEMY TO LIST ]
            this->mob_entities.push_back(enemy);
        }
    }
    this->entities_lock.unlock();
}

Entity* Manager::getEntity(EntGroup group, int index){
    lock_guard<mutex> lock(this->entities_lock);
    switch (group){
    case enemies:
        return this->mob_entities[index];
    case statical:
        return this->static_entities[index];
    }
    return nullptr;
}

int Manager::size(EntGroup group){
    switch (group){
    case enemies:
        return this->mob_entities.size();
    case statical:
        return this->static_entities.size();
    }
    return 0;
}