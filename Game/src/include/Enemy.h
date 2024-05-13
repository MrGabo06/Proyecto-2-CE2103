#ifndef ENEMY_H
#define ENEMY_H
using namespace std;
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
    G_Node<MapChunk>* LastPosition = nullptr; 
public: // Methods
    Enemy(){};
    virtual void shift(){};
    void tracedBack() {
        vector< G_Node<MapChunk>* > path;
        path = backtrack(path, location, LastPosition);
        for(int i=0; i<path.size(); i++){
            route.push(make_tuple(path[i]->data->coordinates[0], path[i]->data->coordinates[1]));
        }
    }
    vector <G_Node<MapChunk>*>backtrack(vector<G_Node<MapChunk>*> path, G_Node<MapChunk>* CurrentPosition, G_Node<MapChunk>* LastPosition){
        int CurX = CurrentPosition->data->coordinates[0];
        int finalX = LastPosition->data->coordinates[0];
        int CurY = CurrentPosition->data->coordinates[0]; 
        int finalY = LastPosition->data->coordinates[0];

        if (CurX == finalX && CurY == finalY){
            return path;
        }
        else{
            for (int i = 0; i < CurrentPosition.total_connected(); i++){
                G_Node<MapChunk>* next = CurrentPosition->getNode(i);
                path.push_back(next);
                backtrack(path, next, LastPosition);
                }

            }
        
            
        }

    };

#endif // ENEMY_H
