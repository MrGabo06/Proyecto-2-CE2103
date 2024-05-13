#ifndef ENEMY_H
#define ENEMY_H

#include "../modules/Queue.h"
#include "Entity.h"

#include <vector>
#include <tuple>
#include <raylib.h> // Asegúrate de incluir el archivo de encabezado adecuado para Vector2
// #include "backtracking1.hpp" // Opcional: puedes incluir backtracking1.hpp o backtracking2.hpp según sea necesario

/// @brief Class for creating 'enemy' type entities for the game
class Enemy : public Entity{
protected: // Atributes
    Queue< std::tuple<int , int> > route;
public: // Methods
    Enemy(){};
    virtual void shift(){};

    void moveTo(MapChunk &newMapChunk, float frameTime);
};

#endif // ENEMY_H
