#ifndef ENEMY_H
#define ENEMY_H

#include "../modules/Queue.h"
#include "Entity.h"
#include "../modules/RandGenerator.h"
#include "Map.h"

#include <vector>
#include <tuple>
#include <raylib.h> // Asegúrate de incluir el archivo de encabezado adecuado para Vector2
// #include "backtracking1.hpp" // Opcional: puedes incluir backtracking1.hpp o backtracking2.hpp según sea necesario

struct Cooldown{
    double action;
    double mov;
};

/// @brief Class for creating 'enemy' type entities for the game
class Enemy : public Entity{
protected: // Atributes
    Generator random_generator;
    Queue< std::tuple<int , int> > route;
    
    int detection_range;
    int route_size;
    int mov_range;
    float speed_multiplier;
    int decision_chances;
    int attack_damage;

public:
    Cooldown cooldown;
public: // Methods

    Enemy(){};

    ~Enemy(){};

    /// @brief In this context, the 'shifting' method make the enemy entity do 'something'(which varies on the context of the entity)
    void shift(Map2D* ref);

    /// @brief Asks the entity generate a random route nearby its initial postion;
    void randomRoute();
};

#endif // ENEMY_H
