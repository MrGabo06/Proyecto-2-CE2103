#include "player.h"

Player::Player(int startGraphX, int startGraphY){
    this->healthPoints = 5;

    this->graphX = startGraphX;
    this->graphY = startGraphY;
    this->setPosition(this->graphX * this->cellSize, this->graphY * this->cellSize);
    this->currentSpriteSheet = movingDownSprite;
    
}

void Player::attack(Enemy* enemy, int64_t time_stamp) {
    this->isAtacking = true;
    if(enemy != nullptr){
        enemy->addHealthPoints(-1);
        if (enemy->getHealth() <= 0){
          enemy->lifetime = time_stamp;
        }
    }
    this->attackTimer = 0.5f;
}

void Player::attack_E(Entity* entity){
    this->isAtacking = true;
    if(ent != nullptr){
      this->addHealthPoints(+1);
      ent->addHealthPoints(-1);
    }
    this->attackTimer = 0.5f;
}


void Player::toggleShield(){
    if (shieldActive) {
        this->addShieldPoints(-2);
    } else {
        this->addShieldPoints(2);
    }
    shieldActive = !shieldActive;
}

void Player::move(float frameTime, const char dir){
    above = &this->currentMap->get(graphAbove, graphX);
    below = &this->currentMap->get(graphBelow, graphX);
    left = &this->currentMap->get(graphY, graphLeft);
    right = &this->currentMap->get(graphY, graphRight);
    belowRight = &this->currentMap->get(graphBelow, graphRight);
    aboveRight = &this->currentMap->get(graphAbove, graphRight);
    belowLeft = &this->currentMap->get(graphBelow, graphLeft);
    
    if (dir == mvUp){
        direction = 1;
        if((above->chunk_type == wall && this->getPosition().y < this->aboveLimit + 2.0f) || (aboveRight->chunk_type == wall && this->getPosition().x > this->rightLimit && this->getPosition().y < this->aboveLimit + 2.0f))
        {
            this->setPosition(-1.0f, aboveLimit);
        } else 
        {
            this->position.y -= entityVerticalSpeed * frameTime;
        }
    }

    if (dir == mvDown) 
    {
        direction = 3;
        if((below->chunk_type == wall && this->getPosition().y > this->belowLimit - 2.0f) || (belowRight->chunk_type == wall && this->getPosition().x > this->rightLimit && this->getPosition().y > this->belowLimit - 2.0f))
        {
            this->setPosition(-1.0f, belowLimit);
        } else 
        {
            this->position.y += entityVerticalSpeed * frameTime;
        }
    }

    if (dir == mvLeft)
    {
        direction = 4;
        if((left->chunk_type == wall && this->getPosition().x < this->leftLimit + 2.0f) || (belowLeft->chunk_type == wall && this->getPosition().y > this->belowLimit && this->getPosition().x < this->leftLimit + 2.0f))
        {
            this->setPosition(leftLimit, -1.0f);
        } else 
        {
            this->position.x -= entityHorizontalSpeed * frameTime;
        }
    }

    if (dir == mvRight)
    {
        direction = 2;
        if((right->chunk_type == wall && this->getPosition().x > this->rightLimit - 2.0f) || (belowRight->chunk_type == wall && this->getPosition().y > this->belowLimit && this->getPosition().x > this->rightLimit - 2.0f))
        {
            this->setPosition(rightLimit, -1.0f);
        } else 
        {
            this->position.x += entityHorizontalSpeed * frameTime;
        }
    }
}

void Player::movePlayer(float frameTime, char contrEntry){
    if (!IsKeyDown(KEY_LEFT) && !IsKeyDown(KEY_RIGHT) && !IsKeyDown(KEY_UP) && !IsKeyDown(KEY_DOWN) && contrEntry != 'w' && contrEntry != 'a' && contrEntry != 's' && contrEntry != 'd')
    {
        // Stop movement
        this->isMoving = false;
    }
    if (this->attackTimer > 0) {
        this->attackTimer -= frameTime * 2.0f;
        if (this->attackTimer <= 0) {
            this->isAtacking = false;
        }
    }

    if (IsKeyDown(KEY_UP) || contrEntry == 'w'){
        this->move(frameTime, Entity::mvUp);
        this->isMoving = true;
        if (isAtacking && shieldActive){
            this->currentSpriteSheet = protAttackUpSprite;
        }else if(isAtacking && !shieldActive){
            this->currentSpriteSheet = attackUpSprite;
        }else if(!isAtacking && shieldActive){
            this->currentSpriteSheet = protUpSprite;
        }else{
            this->currentSpriteSheet = movingUpSprite;
        }
    }

    if (IsKeyDown(KEY_DOWN) || contrEntry == 's'){
        this->move(frameTime, Entity::mvDown);
        this->isMoving = true;
        if (isAtacking && shieldActive){
            this->currentSpriteSheet = protAttackDownSprite;
        }else if(isAtacking && !shieldActive){
            this->currentSpriteSheet = attackDownSprite;
        }else if(!isAtacking && shieldActive){
            this->currentSpriteSheet = protDownSprite;
        }else{
            this->currentSpriteSheet = movingDownSprite;
        }
    }

    if (IsKeyDown(KEY_LEFT) || contrEntry == 'a'){
        this->move(frameTime, Entity::mvLeft);
        this->isMoving = true;
        if (isAtacking && shieldActive){
            this->currentSpriteSheet = protAttackLeftSprite;
        }else if(isAtacking && !shieldActive){
            this->currentSpriteSheet = attackLeftSprite;
        }else if(!isAtacking && shieldActive){
            this->currentSpriteSheet = protLeftSprite;
        }else{
            this->currentSpriteSheet = movingLeftSprite;
        }
    }

    if (IsKeyDown(KEY_RIGHT) || contrEntry == 'd'){
        this->move(frameTime, Entity::mvRight);
        this->isMoving = true;
        if (isAtacking && shieldActive){
            this->currentSpriteSheet = protAttackRightSprite;
        }else if(isAtacking && !shieldActive){
            this->currentSpriteSheet = attackRightSprite;
        }else if(!isAtacking && shieldActive){
            this->currentSpriteSheet = protRightSprite;
        }else{
            this->currentSpriteSheet = movingRightSprite;
        }
    }
  
    if (IsKeyDown(KEY_Q)){
        this->light = !light;
    }

    if (IsKeyPressed(KEY_C)){
        this->toggleShield();
    }

    this->graphX = this->getPosition().x / this->cellSize;
    this->graphY = this->getPosition().y / this->cellSize;

    this->graphAbove = this->graphY - 1;
    this->graphBelow = this->graphY + 1;
    this->graphLeft = this->graphX - 1;
    this->graphRight = this->graphX + 1;

    this->aboveLimit = this->graphY * this->cellSize;
    this->belowLimit = this->graphY * this->cellSize + 26.0f;
    this->leftLimit = this->graphX * this->cellSize;
    this->rightLimit = this->graphX * this->cellSize + 32.0f;
}





