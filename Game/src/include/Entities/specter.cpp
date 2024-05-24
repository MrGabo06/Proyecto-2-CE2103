#include "specter.h"

Specter::Specter(){}

Specter::Specter(int xCord, int yCord, int skill_rates[]){
    // [ INITIALIZE THE ENTITY ]
    this->setPosition(0.f, 0.f);
    this->graphX = xCord;
    this->graphY = yCord;
    ///this->currentSpriteSheet = movingDownSprite;
    this->setProperties(skill_rates);
    switch (type) {
        case TYPE1:
            this->blueUpSprite = LoadTexture("Game/src/resources/entity_assets/blueSpecterUp.png");
            this->blueDownSprite = LoadTexture("Game/src/resources/entity_assets/blueSpecterDown.png");
            this->blueLeftSprite = LoadTexture("Game/src/resources/entity_assets/blueSpecterLeft.png");
            this->blueRightSprite = LoadTexture("Game/src/resources/entity_assets/blueSpecterRight.png");
            break;
        case TYPE2:
            this->redUpSprite = LoadTexture("Game/src/resources/entity_assets/redSpecterUp.png");
            this->redDownSprite = LoadTexture("Game/src/resources/entity_assets/redSpecterDown.png");
            this->redLeftSprite = LoadTexture("Game/src/resources/entity_assets/redSpecterLeft.png");
            this->redRightSprite = LoadTexture("Game/src/resources/entity_assets/redSpecterRight.png");
            break;
        case TYPE3:
            this->grayUpSprite = LoadTexture("Game/src/resources/entity_assets/graySpecterUp.png");
            this->grayDownSprite = LoadTexture("Game/src/resources/entity_assets/graySpecterDown.png");
            this->grayLeftSprite = LoadTexture("Game/src/resources/entity_assets/graySpecterLeft.png");
            this->grayRightSprite = LoadTexture("Game/src/resources/entity_assets/graySpecterDown.png");
            break;
    }

 }

void Specter::setProperties(int scaling[]) {
    this->attributes.cooldown = 5;
    
    // 1.
    this->attributes.damage[0] = scaling[0];
    this->attributes.damage[1] = (scaling[0]*MAX_DAMAGE.specter)/10;
    if (this->attributes.damage[1] == 0){
        this->attributes.damage[1] = 1;
    }

    // 2.
    this->attributes.distance[0] = scaling[1];
    this->attributes.distance[1] = (scaling[1]*MAX_DISTANCE.specter)/10;
    if (this->attributes.distance[1] == 0){
        this->attributes.distance[1] = 1;
    }

    // 3.
    this->attributes.health[0] = scaling[2];
    this->attributes.health[1] = (scaling[2]*MAX_HEALTH.specter)/10;
    if (this->attributes.health[1] == 0){
        this->attributes.health[1] = 1;
    }
    this->healthPoints = this->attributes.health[1];

    // 4.
    this->attributes.range[0] = scaling[3];
    this->attributes.range[1] = (scaling[3]*MAX_RANGE.specter)/10;
    if (this->attributes.range[1] == 0){
        this->attributes.range[1] = 1;
    }

    // 5.
    this->attributes.route_size[0] = scaling[4];
    this->attributes.route_size[1] = (scaling[4]*MAX_ROUTE_SIZE.specter)/10;
    if (this->attributes.route_size[1] == 0){
        this->attributes.route_size[1] = 1;
    }

    // 6.
    this->attributes.speed[0] = (float)scaling[5];
    this->attributes.speed[1] = (scaling[0]*MAX_SPEED.specter)/10;
    if (this->attributes.speed[1] == 0){
        this->attributes.speed[1] = 1.0;
    }
 }