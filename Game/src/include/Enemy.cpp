#include "Enemy.h"


void Enemy::shift(Map2D* ref){
    B_Node< tuple<int,int> > new_coords = this->route.dequeue();
    ref->locate_at(this, get<0>(new_coords.data), get<1>(new_coords.data), true);
    this->route.enqueue(new_coords.data);
}

void Enemy::randomRoute(){
    this->route.enqueue(make_tuple(random_generator.generateInt(0,4), random_generator.generateInt(0,7)));
    this->route.enqueue(make_tuple(random_generator.generateInt(0,7), random_generator.generateInt(0,4)));
};