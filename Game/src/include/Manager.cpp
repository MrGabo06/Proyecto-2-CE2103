#include "Manager.h"
#include <iostream>

Manager::Manager(){
    this->origin = nullptr;
}

Manager::Manager(Map2D* source, int specters, int eyes, int rats, int chocobos, int supers, int treasures, int vases){
    // [ ADD ENTITIES TO VECTORS ]
    this->origin = source;
    this->addEntities(EntityType::SPECTER, specters);
    int specters_to_eyes[] = { specters, specters+eyes};
    this->addEntities(EntityType::EYE, eyes);
    // [ ADD THE SPECTERS AS OBSERVERS OF THE EYES OF THE MAP]
    for (int i = specters_to_eyes[0]; i < specters_to_eyes[1]; i++){
        Eye* eye = static_cast<Eye*>(this->getEntity(EntGroup::enemies,i));
        for (int j = 0; j < specters_to_eyes[0]; j++){
            Specter* specter = static_cast<Specter*>(this->getEntity(EntGroup::enemies,j));
            if (specter == nullptr){
                std::cout << "null instance" << std::endl;
            }
            eye->addObserver(specter);
        }
    }
    this->addEntities(EntityType::RAT, rats);
    this->addEntities(EntityType::CHOCOBO, chocobos);
    this->addEntities(EntityType::SUPER, supers);
    this->addEntities(EntityType::TREASURE, treasures);
    this->addEntities(EntityType::VASE, vases);
}

void Manager::addEntities(EntityType entity_t, int quantity){
    this->entities_lock.lock();
    if ( entity_t == EntityType::TREASURE || entity_t == EntityType::VASE){ // Generate static entities
        Entity* entity = nullptr;
        for (int i = 0; i < quantity; i++){
            // [ CREATE AND SET A NON-CLUTTERING LOCATION FOR ENTITY]
            int location_coords[2] = {randomizer.gen(1,this->origin->grid_size[0]-2), randomizer.gen(1,this->origin->grid_size[1]-2)};
            MapChunk chunk = this->origin->get(location_coords[0], location_coords[1]);
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
            // std::cout << location_coords[0] << "   " << location_coords[1] << std::endl;
            MapChunk chunk = this->origin->get(location_coords[0], location_coords[1]);
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
                // std::cout << location_coords[0] << "   " << location_coords[1] << std::endl;
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

int Manager::size(EntGroup group)
{
    switch (group)
    {
    case enemies:
        return this->mob_entities.size();
    case statical:
        return this->static_entities.size(); 
    }
    return 0;
}

void Manager::killAll(int64_t current_time){
    for (int i = 0; i<this->mob_entities.size(); i++){
        Enemy* enemy = this->mob_entities[i];
        if (enemy->getHealth() > 0){
            enemy->addHealthPoints(-enemy->getHealth());
            enemy->lifetime = current_time;
        }
    }

    for (int i = 0; i<this->static_entities.size(); i++){
        Entity* entity = this->static_entities[i];
        entity->addHealthPoints(-entity->getHealth());
    }
}

void Manager::evolve(int specters, int eyes, int rats, int chocobos, int supers, int treasures, int vases)
{
    // std::cout << "OLD STAT(HP): " << this->stats[0] << std::endl;
    // std::cout << "OLD STAT(DMG): " << this->stats[1] << std::endl;
    // std::cout << "OLD STAT(RNG): " << this->stats[2] << std::endl;
    // std::cout << "OLD STAT(DST): " << this->stats[3] << std::endl;
    // std::cout << "OLD STAT(RTS): " << this->stats[4] << std::endl;
    // std::cout << "OLD STAT(SPD): " << this->stats[5] << std::endl;
    // [ GET A NEW SET OF STATS FOR ENTITIES ]
    Enemy* best_prospects[] = {nullptr, nullptr};
    for (auto enemy : this->mob_entities){
        if ( best_prospects[0] == nullptr){
            best_prospects[0] = enemy;
        }
        if ( best_prospects[1] == nullptr){
            best_prospects[1] = enemy;
        }
        if (best_prospects[0] != nullptr && best_prospects[1] != nullptr){
            if (enemy->lifetime > best_prospects[0]->lifetime){
                best_prospects[0] = enemy;
            } else if (enemy->lifetime > best_prospects[1]->lifetime){
                best_prospects[1] = enemy;
            }
        }
    }

    int total_inherits = randomizer.gen(1,6);
    int inheritable_stats[total_inherits];
    for (int i = 0; i < total_inherits; i++){
        inheritable_stats[i] = randomizer.gen(0,5);
    }
    int new_att_set[6] = { 0 };
    for (int i = 0; i < 6; i++){
        bool inherited = false;
        for (auto selection : inheritable_stats){
            int random_parent = randomizer.gen(0,1);
            if (i == selection){
                if (i == 0){
                    new_att_set[i] = best_prospects[random_parent]->getAttributes().health[0];
                }
                if (i == 1){
                    new_att_set[i] = best_prospects[random_parent]->getAttributes().damage[0];
                }
                if (i == 2){
                    new_att_set[i] = best_prospects[random_parent]->getAttributes().range[0];
                }
                if (i == 3){
                    new_att_set[i] = best_prospects[random_parent]->getAttributes().distance[0];
                }
                if (i == 4){
                    new_att_set[i] = best_prospects[random_parent]->getAttributes().route_size[0];
                }
                if (i == 5){
                    new_att_set[i] = best_prospects[random_parent]->getAttributes().speed[0];
                }
                inherited = true;
            }
        }
        if (!inherited){
            new_att_set[i] = randomizer.gen(1,10);
        }
    }

    for (int i = 0; i < 6; i++){
        this->stats[i] = new_att_set[i];
    }
    // [ CLEAR ANY ENTITIES ON THE ARRAYS ]
    while (this->mob_entities.size() > 0){
        Enemy* enemy = this->mob_entities[this->mob_entities.size()-1];
        this->mob_entities.pop_back();
        delete enemy;
    }

    while (this->static_entities.size() > 0){
        Entity* entity = this->static_entities[this->static_entities.size()-1];
        this->static_entities.pop_back();
        delete entity;
    }

    // [ INSERT THE NEWLY CREATED ENTITIES ]
    this->addEntities(EntityType::SPECTER, specters);
    int specters_to_eyes[] = { specters, specters+eyes};
    this->addEntities(EntityType::EYE, eyes);
    // [ ADD THE SPECTERS AS OBSERVERS OF THE EYES OF THE MAP]
    for (int i = specters_to_eyes[0]; i < specters_to_eyes[1]; i++){
        Eye* eye = static_cast<Eye*>(this->getEntity(EntGroup::enemies,i));
        for (int j = 0; j < specters_to_eyes[0]; j++){
            Specter* specter = static_cast<Specter*>(this->getEntity(EntGroup::enemies,j));
            eye->addObserver(specter);
        }
    }
    this->addEntities(EntityType::RAT, rats);
    this->addEntities(EntityType::CHOCOBO, chocobos);
    this->addEntities(EntityType::SUPER, supers);
    this->addEntities(EntityType::TREASURE, treasures);
    this->addEntities(EntityType::VASE, vases);

    // std::cout << "NEW STAT(HP): " << this->stats[0] << std::endl;
    // std::cout << "NEW STAT(DMG): " << this->stats[1] << std::endl;
    // std::cout << "NEW STAT(RNG): " << this->stats[2] << std::endl;
    // std::cout << "NEW STAT(DST): " << this->stats[3] << std::endl;
    // std::cout << "NEW STAT(RTS): " << this->stats[4] << std::endl;
    // std::cout << "NEW STAT(SPD): " << this->stats[5] << std::endl;
}
