#ifndef ENEMY_H
#define ENEMY_H

#include <vector>
#include "raylib.h" // Asegúrate de incluir el archivo de encabezado adecuado para Vector2
#include "backtracking1.hpp" // Opcional: puedes incluir backtracking1.hpp o backtracking2.hpp según sea necesario

class Enemy {
public:
    bool moveTowardsPosition(const Vector2& targetPosition, std::vector<Vector2>& path);
};

#endif // ENEMY_H
