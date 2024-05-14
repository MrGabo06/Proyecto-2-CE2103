#include "specter.h"

Specter::Specter(){
    // [ INITIALIZE THE ENTITY ]
    this->setHealthPoints(1);
    this->setPosition(0.f,0.f);
    this->currentSpriteSheet = movingDownSprite;

    this->cooldown = {1.5 , 1.5};

    this->target = nullptr;
    this->location = nullptr;
    this->LastPosition = nullptr;

    this->routing = true;
    this->engaging = false;
    this->returning = false;

    int default_properties[] = { 3, 3, 3, 3, 3, 3};
    this->setProperties(default_properties);
}

Specter::Specter(float xCord, float yCord, int skill_rates[]){
    // [ INITIALIZE THE ENTITY ]
    this->setHealthPoints(5);
    this->setPosition(xCord, yCord);
    this->currentSpriteSheet = movingDownSprite;

    this->cooldown = { 1.5 , 1.5};

    this->target = nullptr;
    this->location = nullptr;
    this->LastPosition = nullptr;

    this->routing = true;
    this->engaging = false;
    this->returning = false;

    this->setProperties(skill_rates);
 }

void Specter::setProperties(int scaling[]) {
    this->detection_range = (scaling[0]*MAX_DETECTION.specter)/10;
    if (this->detection_range == 0){
        this->detection_range = 1;
    }

    this->route_size = (scaling[1]*MAX_ROUTE.specter)/10;
    if (this->route_size == 0){
        this->route_size = 1;
    }

    this->mov_range = (scaling[2]*MAX_MOVEMENT.specter)/10;
    if (this->mov_range == 0){
        this->mov_range = 1;
    }
    this->speed_multiplier = (float(scaling[3])*MAX_SPEED.specter)/10.f;

    this->decision_chances = (scaling[4]*MAX_DECISIONS.specter)/10;
    if (this->decision_chances == 0){
        this->decision_chances = 1;
    }
    this->attack_damage = (scaling[5]*MAX_ATTACK.specter)/10;
    if (this->attack_damage == 0){
        this->attack_damage = 1;
    }
 }