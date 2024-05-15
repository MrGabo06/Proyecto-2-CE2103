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


void Enemy::shift(Map2D* ref, float frameTime){
    if (this->routing){
        this->patrol(frameTime);
    }
    if (this->returning){
        this->returning = false;
        this->routing = true;
    }
    if (this->engaging){
        if(this->target != nullptr){
            if (this->target->getLocation()->data.chunk_type != ChunkType::safe){
                if (this->rangeToEntity(this->target, true)){
                    this->attack();
                } else {
                    this->moveTo(this->target->getLocation()->data, frameTime);
                }
            } else {
                this->disengage();
            }
        }
    }
}

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
    this->target = entity;
};

void Enemy::attack(){
    this->target->setHealthPoints(0);
};

void Enemy::patrol(float frameTime){
    MapChunk chunk = this->route.peek();
    this->moveTo(chunk, frameTime);
    if (this->graphY == chunk.coordinates[0] && this->graphX == chunk.coordinates[1]){
        this->route.enqueue(this->route.dequeue().data);
    }
};

bool Enemy::rangeToEntity(Entity* entity, bool attacking){
    int range = this->detection_range;
    if (attacking){
        range = 15;
    }
    Vector2 other = entity->getPosition();
    Vector2 current = this->getPosition();
    // [ VALIDATION IN X ]
    bool conditionX = (other.x < current.x + range) && (other.x > current.x - range);
    // [ VALIDATION IN Y ]
    bool conditionY = (other.y < current.y + range) && (other.y > current.y - range);

    return conditionX && conditionY;
};