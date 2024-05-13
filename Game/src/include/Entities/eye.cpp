#include "eye.h"

Eye::Eye() {
    // [ INITIALIZE THE ENTITY ]
    this->setHealthPoints(1);
    this->setPosition(0,0);
    this->currentSpriteSheet = movingDownSprite;

    this->cooldown.action = 4.5;
    this->cooldown.mov = 2.5;

    this->detection_range = 1;
    this->route_size = 2;
    this->mov_range = 2;
    this->speed_multiplier = 0.15f;
    this->decision_chances = 1;
    this->attack_damage = 1;
}

Eye::Eye(float xCord, float yCord, int skill_rates[]){
    this->setHealthPoints(5);
    this->setPosition(xCord, yCord);
    this->currentSpriteSheet = movingDownSprite;

    this->cooldown.action = 4.5;
    this->cooldown.mov = 2.5;

    this->detection_range = (skill_rates[0]*MAX_DET_RANGE)/10;
    if (this->detection_range == 0){
        this->detection_range = 1;
    }

    this->route_size = (skill_rates[1]*MAX_ROUTE_SIZE)/10;
    if (this->route_size == 0){
        this->route_size = 1;
    }

    this->mov_range = (skill_rates[2]*MAX_MOV_RANGE)/10;
    if (this->mov_range == 0){
        this->mov_range = 1;
    }

    this->speed_multiplier = (float(skill_rates[3])*MAX_SPEED_MULT)/10.f;

    this->decision_chances = (skill_rates[4]*MAX_DECISIONS)/10;
    if (this->decision_chances == 0){
        this->decision_chances = 1;
    }

    this->attack_damage = (skill_rates[5]*MAX_ATTACK_DMG)/10;
    if (this->attack_damage == 0){
        this->attack_damage = 1;
    }
}