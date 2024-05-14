#include "Enemy.h"

void Enemy::moveTo(MapChunk &newMapChunk, float frameTime){
    if (this->getPosition().x < newMapChunk.center().x -20.0f){
        this->move(frameTime,Entity::mvRight);
    }

    if (this->getPosition().x > newMapChunk.center().x + 20.0f){
        this->move(frameTime ,Entity::mvLeft);
    }

    if (this->getPosition().y < newMapChunk.center().y - 20.0f){
        this->move(frameTime ,Entity::mvDown);
    }
    
    if (this->getPosition().y > newMapChunk.center().y + 20.0f){
        this->move(frameTime, Entity::mvUp);
    }
}


void Enemy::shift(Map2D* ref){

}

void Enemy::generateRoute(){
    // this->route.enqueue(make_tuple(random_generator.generateInt(0,4), random_generator.generateInt(0,7)));
    // this->route.enqueue(make_tuple(random_generator.generateInt(0,7), random_generator.generateInt(0,4)));
};

void Enemy::traceback(){
    // vector< G_Node<MapChunk>* > path;
    // path = backtrack(path, location, LastPosition);
    // for(int i=0; i<path.size(); i++){
    //     route.push(make_tuple(path[i]->data->coordinates[0], path[i]->data->coordinates[1]));
    // }
};

vector< G_Node<MapChunk>* > Enemy::backtrack(vector<G_Node<MapChunk>*> path, G_Node<MapChunk>* CurrentPosition, G_Node<MapChunk>* LastPosition){
    vector <G_Node<MapChunk>*> res;
    // int CurX = CurrentPosition->data->coordinates[0];
    // int finalX = LastPosition->data->coordinates[0];
    // int CurY = CurrentPosition->data->coordinates[0]; 
    // int finalY = LastPosition->data->coordinates[0];

    // if (CurX == finalX && CurY == finalY){
    //     return path;
    // } else {
    //     for (int i = 0; i < CurrentPosition.total_connected(); i++){
    //         G_Node<MapChunk>* next = CurrentPosition->getNode(i);
    //         path.push_back(next);
    //         backtrack(path, next, LastPosition);
    //     }
    // }
    return res;
};

void Enemy::setTarget(Entity* entity){

};

void Enemy::attack(){

};

void Enemy::follow(){

};