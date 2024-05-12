#ifndef BACKTRACKING_H
#define BACKTRACKING_H

#include <vector>
#include "raylib.h" // Asegúrate de incluir el archivo de encabezado adecuado para Vector2

class Backtracking {
public:
    static bool moveTowardsPosition(const Vector2& currentPosition, const Vector2& targetPosition, std::vector<Vector2>& path);
};

#endif // BACKTRACKING1_H
