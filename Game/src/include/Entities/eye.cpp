#include "eye.h"

Eye::Eye(){}

Eye::Eye(int xCord, int yCord, int skill_rates[]){
    // [ INITIALIZE THE ENTITY ]
    this->setPosition(0.f, 0.f);
    this->graphX = xCord;
    this->graphY = yCord;
    this->currentSpriteSheet = movingDownSprite;
    this->setProperties(skill_rates);
 }

 void Eye::setTarget(Entity *entity){
    this->target = entity;
    this->detected = entity;
    this->notify();
 }

void Eye::setProperties(int scaling[]) {
    this->attributes.cooldown = 2;
    
    // 1.
    this->attributes.damage[0] = scaling[0];
    this->attributes.damage[1] = (scaling[0]*MAX_DAMAGE.eye)/10;

    // 2.
    this->attributes.distance[0] = scaling[1];
    this->attributes.distance[1] = (scaling[1]*MAX_DISTANCE.eye)/10;

    // 3.
    this->attributes.health[0] = scaling[2];
    this->attributes.health[1] = (scaling[2]*MAX_HEALTH.eye)/10;
    if (this->attributes.health[1] == 0){
        this->attributes.health[1] = 1;
    }
    this->healthPoints = this->attributes.health[1];

    // 4.
    this->attributes.range[0] = scaling[3];
    this->attributes.range[1] = (scaling[3]*MAX_RANGE.eye)/10;
    if (this->attributes.range[1] == 0){
        this->attributes.range[1] = 1;
    }

    // 5.
    this->attributes.route_size[0] = scaling[4];
    this->attributes.route_size[1] = (scaling[4]*MAX_ROUTE_SIZE.eye)/10;

    // 6.
    this->attributes.speed[0] = (float)scaling[5];
    this->attributes.speed[1] = (scaling[0]*MAX_SPEED.eye)/10;
 }