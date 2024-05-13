#include "Manager.h"

Manager::Manager(){
    this->origin = nullptr;
}

Manager::Manager(Map2D* source, int specters, int eyes, int rats, int chocobos, int supers, int treasures, int vases){
    // [ SET THE ATTRIBUTE SCALING FOR ENEMIES ]
    for (int x = 0; x < 6; x++){
        this->stats[x] = 5;
    }
    // [ LOAD ENEMIES ]
    this->origin = source;
    int max_enemies = specters+eyes+rats+chocobos+supers;
    for (int i = 0; i<max_enemies; i++){
        if ( i < specters){
            Enemy* specter = new Specter(0.f, 0.f,this->stats);
            source->locate_at(specter, randomizer.generateInt(0, source->grid_size[0]), randomizer.generateInt(0, source->grid_size[1]) , true);
            specter->randomRoute();
            this->mob_entities.push_back(specter);
        }
        if ( i < eyes){
            Enemy* eye = new Eye(0.f,0.f,this->stats);
            source->locate_at(eye, randomizer.generateInt(0, source->grid_size[0]), randomizer.generateInt(0, source->grid_size[1]) , true);
            eye->randomRoute();
            this->mob_entities.push_back(eye);
        }
        if ( i < rats){
            Enemy* rat = new Rat(0.f, 0.f, this->stats);
            source->locate_at(rat, randomizer.generateInt(0, source->grid_size[0]), randomizer.generateInt(0, source->grid_size[1]) , true);
            rat->randomRoute();
            this->mob_entities.push_back(rat);
        }
        if ( i < chocobos){
            Enemy* bird = new Chocobo(0.f, 0.f, this->stats);
            source->locate_at(bird, randomizer.generateInt(0, source->grid_size[0]), randomizer.generateInt(0, source->grid_size[1]) , true);
            bird->randomRoute();
            this->mob_entities.push_back(bird);
        }
        if ( i < supers){
            Enemy* super = new Super(0.f, 0.f, this->stats);
            source->locate_at(super, randomizer.generateInt(0, source->grid_size[0]), randomizer.generateInt(0, source->grid_size[1]) , true);
            super->randomRoute();
            this->mob_entities.push_back(super);
        }
    }
    // [ LOAD OTHER ENTITIES ]
    int max_statics = treasures+vases;
    for (int i = 0; i < max_statics; i++){
        if (i < treasures){
            Entity* treasure = new Treasure(0.f, 0.f);
            source->locate_at(treasure, randomizer.generateInt(0, source->grid_size[0]), randomizer.generateInt(0, source->grid_size[1]) , true);
            this->static_entities.push_back(treasure);
        }
        if (i < vases){
            Entity* vase = new Vase(0.f, 0.f);
            source->locate_at(vase, randomizer.generateInt(0, source->grid_size[0]), randomizer.generateInt(0, source->grid_size[1]) , true);
            this->static_entities.push_back(vase);
        }
    }
    // [ START THE CONTROLLER THREAD ]
    this->active_status = true;
    thread(&Manager::control, this).detach();
}

void Manager::addMapRef(Map2D* source){
    this->origin = source;
}

void Manager::addEntities(EntityType entity_t, int quantity){

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

void Manager::toggle(){
    this->status_lock.lock();

    this->active_status = !this->active_status;

    this->status_lock.unlock();
}

bool Manager::getStatus(){
    lock_guard<mutex> lock(this->status_lock);
    return this->active_status;
}

void Manager::control(){
    clock_t start = clock();
    while (this->getStatus()){
        // clock_t current = clock();
        // double elapsed_time = (current - start) / (double)CLOCKS_PER_SEC;

        this->entities_lock.lock();
        for (int i = 0; i < this->mob_entities.size(); i++){
            // double timer = elapsed_time - this->mob_entities[i]->cooldown.action;
            // if (timer > 0 && timer < 0.2){
            //     this->mob_entities[i]->shift(this->origin);
            // }
            // timer = elapsed_time - this->mob_entities[i]->cooldown.mov;
            // if (timer > 0 && timer < 0.2){
            //     this->mob_entities[i]->shift(this->origin);
            // }
            this->mob_entities[i]->shift(this->origin);
        }
        this->entities_lock.unlock();

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}