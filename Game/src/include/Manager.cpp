#include "Manager.h"

Manager::Manager()
{
    this->origin = nullptr;
}

Manager::Manager(Map2D *source, int specters, int eyes, int rats, int chocobos, int supers, int treasures, int vases)
{
    // [ LOAD ENEMIES ]
    this->origin = source;
    int max_enemies = specters + eyes + rats + chocobos + supers;
    for (int i = 0; i < max_enemies; ++i)
    {
        if (i <= specters)
        {
            Enemy *specter = new Specter(0.f, 0.f);
            source->locate_at(specter, 1, 1, true);
            this->mob_entities.push_back(specter);
        }
        if (i <= eyes)
        {
            Enemy *eye = new Eye(0.f, 0.f);
            source->locate_at(eye, 1, 1, true);
            this->mob_entities.push_back(eye);
        }
        if (i <= rats)
        {
            Enemy *rat = new Rat(0.f, 0.f);
            source->locate_at(rat, 1, 1, true);
            this->mob_entities.push_back(rat);
        }
        if (i <= chocobos)
        {
            Enemy *bird = new Chocobo(0.f, 0.f);
            source->locate_at(bird, 1, 1, true);
            this->mob_entities.push_back(bird);
        }
        if (i <= supers)
        {
            Enemy *super = new Super(0.f, 0.f);
            source->locate_at(super, 2, 2, true);
            this->mob_entities.push_back(super);
        }
    }

    // [ LOAD OTHER ENTITIES ]
    int max_statics = treasures + vases;
    for (int i = 0; i < max_statics; ++i)
    {
        if (i <= treasures)
        {
            Entity *treasure = new Treasure(0.f, 0.f);
            source->locate_at(treasure, 4, 4, true);
            this->static_entities.push_back(treasure);
        }
        if (i <= vases)
        {
            Entity *vase = new Vase(0.f, 0.f);
            source->locate_at(vase, 7, 3, true);
            this->static_entities.push_back(vase);
        }
    }
}

void Manager::addMapRef(Map2D *source)
{
    this->origin = source;
}

void Manager::addEntities(EntityType entity_t, int quantity)
{
}

Entity *Manager::getEntity(EntGroup group, int index)
{
    switch (group)
    {
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

void Manager::control()
{
    thread({

           })
        .detach();
}