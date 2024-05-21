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
    Queue< MapChunk > route;
    Queue< MapChunk > sub_route;

    G_Node< MapChunk >* LastPosition;
    Entity* target;
    
    // { Enemy properties }
    int detection_range;
    int route_size;
    int mov_range;
    float speed_multiplier;
    int decision_chances;
    int attack_damage;

    Cooldown cooldown;

    int lifetime;

    // { Enemy operational states }
    bool routing;
    bool engaging;
    bool returning;

public: // Methods

    Enemy(){};

    ~Enemy(){};

    /// @brief In this context, the 'shifting' method make the enemy entity do 'something'(which varies on the context of the entity)
    void shift(float frameTime, int64_t time_stamp);

    /// @brief Sets an entity as the target of this enemy
    /// @param entity: reference to the entity
    void setTarget(Entity* entity);

    /// @brief Asks the entity to attack its current target
    virtual void attack();

    /// @brief Asks the entity to continue its patrol route
    void patrol(float frameTime);

    /// @brief Returns the entity to its last position (only if entity was engaged in combat)
    /// @param frameTime 
    void traceback(float frameTime);

    /// @brief Engages the entity into offensive state
    void engage();

    /// @brief Disengages the entity into its normal state
    void disengage();

    /// @brief Determines if another entity is in range to this instance
    /// @param entity: reference to other entity
    /// @param attacking: changes the range from [VISION] to [ATTACK]
    /// @return True or False
    bool rangeToEntity(Entity* entity, bool attacking);

    /// @brief Moves the entity to the specified chunk
    /// @param newMapChunk 
    /// @param frameTime 
    void moveTo(MapChunk &newMapChunk, float frameTime);

    /// @brief Generates a random patrol route for entity
    /// @param map 
    void generateRoute(Map2D* map);
    
protected:

    /// @brief Sets the enemy properties based on a rating (1-10) 
    /// @param scaling: array(6) of ratings
    virtual void setProperties(int scaling[]){};

};

#endif // ENEMY_H
