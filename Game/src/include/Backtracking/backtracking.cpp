#include "backtracking.hpp"

bool Backtracking::moveTowardsPosition(const Vector2& currentPosition, const Vector2& targetPosition, std::vector<Vector2>& path) {
    // Definir las direcciones posibles de movimiento
    const std::vector<Vector2> directions = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };

    // Verificar si ya estamos en la posición objetivo
    if (currentPosition == targetPosition) {
        return true;
    }

    // Iterar a través de las direcciones posibles
    for (const Vector2& direction : directions) {
        Vector2 newPosition = currentPosition + direction;

        // Verificar si la nueva posición es válida (puedes implementar esta función)
        if (isValidPosition(newPosition)) {
            // Agregar la nueva posición al camino
            path.push_back(newPosition);

            // Llamar recursivamente a la función para continuar moviéndose hacia la posición objetivo
            if (moveTowardsPosition(newPosition, targetPosition, path)) {
                return true; // Se encontró una solución válida
            }

            // Si no se encontró una solución válida desde esta posición, retroceder
            path.pop_back();
        }
    }

    return false; // No se encontró una solución válida desde esta posición
}
