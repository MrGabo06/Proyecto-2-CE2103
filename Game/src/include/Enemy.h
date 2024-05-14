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

struct Cooldown{
    double action;
    double mov;
};

using namespace std;
/// @brief Class for creating 'enemy' type entities for the game
class Enemy : public Entity{
protected: // Atributes
    Generator random_generator;
    Queue< std::tuple<int , int> > route;
    G_Node<MapChunk>* LastPosition = nullptr;
    
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

    void moveTo(MapChunk &newMapChunk, float frameTime);

    // void tracedBack() {
    //     vector< G_Node<MapChunk>* > path;
    //     path = backtrack(path, location, LastPosition);
    //     for(int i=0; i<path.size(); i++){
    //         route.push(make_tuple(path[i]->data->coordinates[0], path[i]->data->coordinates[1]));
    //     }
    // }
    // vector <G_Node<MapChunk>*>backtrack(vector<G_Node<MapChunk>*> path, G_Node<MapChunk>* CurrentPosition, G_Node<MapChunk>* LastPosition){
    //     int CurX = CurrentPosition->data->coordinates[0];
    //     int finalX = LastPosition->data->coordinates[0];
    //     int CurY = CurrentPosition->data->coordinates[0]; 
    //     int finalY = LastPosition->data->coordinates[0];

    //     if (CurX == finalX && CurY == finalY){
    //         return path;
    //     }
    //     else{
    //         for (int i = 0; i < CurrentPosition.total_connected(); i++){
    //             G_Node<MapChunk>* next = CurrentPosition->getNode(i);
    //             path.push_back(next);
    //             backtrack(path, next, LastPosition);
    //             }

    //         }
        
            
    //     }

    };

#endif // ENEMY_H
