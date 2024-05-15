#ifndef ENEMY_H
#define ENEMY_H

#include "../modules/Queue.h"
#include "Entity.h"
#include "../modules/RandGenerator.h"
#include "enemy_properties.hpp"
#include "Map.h"

#include <vector>
#include <tuple>
#include <raylib.h>

class Map2D;

struct Cooldown{
    int action;
    int movement;
};

using namespace std;
/// @brief Class for creating 'enemy' type entities for the game
class Enemy : public Entity{
protected: // Atributes
    Generator random;

    // { Pathfinding variables }
    G_Node< MapChunk >* LastPosition;
    Entity* target;
    
    // { Enemy properties }
    int detection_range;
    int route_size;
    int mov_range;
    float speed_multiplier;
    int decision_chances;
    int attack_damage;

    // { Enemy operational states }
    bool routing;
    bool engaging;
    bool returning;

public:
    // { Pathfinding variables }
    Queue< MapChunk > route;

    Cooldown cooldown;
public: // Methods

    Enemy(){};

    ~Enemy(){};

    /// @brief In this context, the 'shifting' method make the enemy entity do 'something'(which varies on the context of the entity)
    void shift(Map2D* ref, float frameTime);

    /// @brief Sets an entity as the target of this enemy
    /// @param entity: reference to the entity
    void setTarget(Entity* entity);

    /// @brief Asks the entity to attack its current target
    virtual void attack();

    /// @brief Asks the entity to continue its patrol route
    void patrol(float frameTime);

    void engage(){
        this->engaging = true;
        this->returning = false;
        this->routing = false;
    };

    void disengage(){
        this->engaging = false;
        this->returning = true;
        this->routing = false;
    };

    bool rangeToEntity(Entity* entity, bool attacking);

    /// @brief Moves the entity to the specified chunk
    /// @param newMapChunk 
    /// @param frameTime 
    void moveTo(MapChunk &newMapChunk, float frameTime);

    /// @brief Goes to back to previous position and returns to normal behavior
    void traceback();
    
protected:

    /// @brief Sets the enemy properties based on a rating (1-10) 
    /// @param scaling: array(6) of ratings
    virtual void setProperties(int scaling[]){};

private:
    /// @brief Backtracks to previous position before engaging
    /// @param path 
    /// @param CurrentPosition 
    /// @param LastPosition 
    /// @return 
    vector< G_Node<MapChunk>* > backtrack(vector<G_Node<MapChunk>*> path, G_Node<MapChunk>* CurrentPosition, G_Node<MapChunk>* LastPosition);

};

#endif // ENEMY_H
