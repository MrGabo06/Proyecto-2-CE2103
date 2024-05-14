#include "Manager.h"

Manager::Manager(){
    this->origin = nullptr;
}

Manager::Manager(Map2D* source, int specters, int eyes, int rats, int chocobos, int supers, int treasures, int vases){
    // [ SET THE ATTRIBUTE SCALING FOR ENEMIES ]
    for (int x = 0; x < 6; x++){
        this->stats[x] = 5;
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

void Manager::addMapRef(Map2D* source){
    this->origin = source;
}

void Manager::addEntities(EntityType entity_t, int quantity){
    this->entities_lock.lock();
    switch (entity_t){
    case (CHOCOBO):
        for ( int i = 0; i < quantity; i++){
            Enemy* chocobo = new Chocobo(0.f, 0.f, this->stats);
            this->origin->locate_at(chocobo,randomizer.generateInt(0, this->origin->grid_size[0]-1),randomizer.generateInt(0, this->origin->grid_size[1]-1), true);
            this->mob_entities.push_back(chocobo);
        }
        break;
    case (EYE):
        for ( int i = 0; i < quantity; i++){
            Enemy* eye = new Eye(0.f, 0.f, this->stats);
            this->origin->locate_at(eye,randomizer.generateInt(0, this->origin->grid_size[0]-1),randomizer.generateInt(0, this->origin->grid_size[1]-1), true);
            this->mob_entities.push_back(eye);
        }
        break;
    case (RAT):
        for ( int i = 0; i < quantity; i++){
            Enemy* rat = new Rat(0.f, 0.f, this->stats);
            this->origin->locate_at(rat,randomizer.generateInt(0, this->origin->grid_size[0]-1),randomizer.generateInt(0, this->origin->grid_size[1]-1), true);
            this->mob_entities.push_back(rat);
        }
        break;
    case (SPECTER):
        for ( int i = 0; i < quantity; i++){
            Enemy* specter = new Specter(0.f, 0.f, this->stats);
            this->origin->locate_at(specter,randomizer.generateInt(0, this->origin->grid_size[0]-1),randomizer.generateInt(0, this->origin->grid_size[1]-1), true);
            this->mob_entities.push_back(specter);
        }
        break;
    case (SUPER):
        for ( int i = 0; i < quantity; i++){
            Enemy* boss = new Super(0.f, 0.f, this->stats);
            this->origin->locate_at(boss,randomizer.generateInt(0, this->origin->grid_size[0]-1),randomizer.generateInt(0, this->origin->grid_size[1]-1), true);
            this->mob_entities.push_back(boss);
        }
        break;
    case (TREASURE):
        for ( int i = 0; i < quantity; i++){
            Entity* chest = new Treasure(0.f, 0.f);
            this->origin->locate_at(chest,randomizer.generateInt(0, this->origin->grid_size[0]-1),randomizer.generateInt(0, this->origin->grid_size[1]-1), true);
            this->static_entities.push_back(chest);
        }
        break;
    case (VASE):
        for ( int i = 0; i < quantity; i++){
            Entity* vase = new Vase(0.f, 0.f);
            this->origin->locate_at(vase,randomizer.generateInt(0, this->origin->grid_size[0]-1),randomizer.generateInt(0, this->origin->grid_size[1]-1), true);
            this->static_entities.push_back(vase);
        }
        break;
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