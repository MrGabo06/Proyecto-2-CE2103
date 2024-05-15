#include "chocobo.h"

Chocobo::Chocobo(){
    // [ INITIALIZE THE ENTITY ]
    this->healthPoints = 1;
    this->setPosition(0.f,0.f);
    this->currentSpriteSheet = movingDownSprite;

    this->cooldown = { 2, 1};

    this->target = nullptr;
    this->location = nullptr;
    this->LastPosition = nullptr;

    this->routing = true;
    this->engaging = false;
    this->returning = false;

    int default_properties[] = { 3, 3, 3, 3, 3, 3};
    this->setProperties(default_properties);
}

Chocobo::Chocobo(int xCord, int yCord, int skill_rates[]){
    // [ INITIALIZE THE ENTITY ]
    this->healthPoints = 3;
    this->setPosition(0.f, 0.f);
    this->graphX = xCord;
    this->graphY = yCord;
    this->currentSpriteSheet = movingDownSprite;

    this->cooldown = { 2, 1};

    this->target = nullptr;
    this->location = nullptr;
    this->LastPosition = nullptr;

    this->routing = true;
    this->engaging = false;
    this->returning = false;

    this->setProperties(skill_rates);
 }

 void Chocobo::setProperties(int scaling[]) {
    this->detection_range = (scaling[0]*MAX_DETECTION.chocobo)/10;
    if (this->detection_range == 0){
        this->detection_range = 1;
    }

    this->route_size = (scaling[1]*MAX_ROUTE.chocobo)/10;
    if (this->route_size == 0){
        this->route_size = 1;
    }

    this->mov_range = (scaling[2]*MAX_MOVEMENT.chocobo)/10;
    if (this->mov_range == 0){
        this->mov_range = 1;
    }
    this->speed_multiplier = (float(scaling[3])*MAX_SPEED.chocobo)/10.f;

    this->decision_chances = (scaling[4]*MAX_DECISIONS.chocobo)/10;
    if (this->decision_chances == 0){
        this->decision_chances = 1;
    }
    this->attack_damage = (scaling[5]*MAX_ATTACK.chocobo)/10;
    if (this->attack_damage == 0){
        this->attack_damage = 1;
    }
 }
