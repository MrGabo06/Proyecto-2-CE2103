#include "player.h"

void Player::attack()
{
    this->isAtacking = true;
    if (direction == 1)
    {
    }
    if (direction == 2)
    {
    }
    if (direction == 3)
    {
    }
    if (direction == 4)
    {
    }
}

void Player::move(float frameTime, const char dir)
{
    above = &this->currentMap->get(graphAbove, graphX);
    below = &this->currentMap->get(graphBelow, graphX);
    left = &this->currentMap->get(graphY, graphLeft);
    right = &this->currentMap->get(graphY, graphRight);
    belowRight = &this->currentMap->get(graphBelow, graphRight);
    aboveRight = &this->currentMap->get(graphAbove, graphRight);
    belowLeft = &this->currentMap->get(graphBelow, graphLeft);
    
    if (dir == mvUp)
    {
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

void Player::movePlayer(float frameTime)
{
    if (IsKeyDown(KEY_SPACE))
    {
        this->attack();
    }
    if (!IsKeyDown(KEY_SPACE))
    {
        this->isAtacking = false;   
    }
    if (!IsKeyDown(KEY_LEFT) && !IsKeyDown(KEY_RIGHT) && !IsKeyDown(KEY_UP) && !IsKeyDown(KEY_DOWN))
    {
        this->isMoving = false;
    }

    if (IsKeyDown(KEY_UP))
    {
        this->move(frameTime, Entity::mvUp);
        this->isMoving = true;
        if (isAtacking){
            this->currentSpriteSheet = attackUpSprite;
        }else{
            this->currentSpriteSheet = movingUpSprite;
        }
    }

    if (IsKeyDown(KEY_DOWN))
    {
        this->move(frameTime, Entity::mvDown);
        this->isMoving = true;
        if (isAtacking){
            this->currentSpriteSheet = attackDownSprite;
        }else{
            this->currentSpriteSheet = movingDownSprite;
        }
    }

    if (IsKeyDown(KEY_LEFT))
    {
        this->move(frameTime, Entity::mvLeft);
        this->isMoving = true;
        if (isAtacking){
            this->currentSpriteSheet = attackLeftSprite;
        }else{
            this->currentSpriteSheet = movingLeftSprite;
        }
    }

    if (IsKeyDown(KEY_RIGHT))
    {
        this->move(frameTime, Entity::mvRight);
        this->isMoving = true;
        if (isAtacking){
            this->currentSpriteSheet = attackRightSprite;
        }else{
            this->currentSpriteSheet = movingRightSprite;
        }
    }

    if (this->getPosition().x < this->worldLeftLimit)
    {
        this->setPosition(this->worldLeftLimit, -1.0f);
    }

    if (this->getPosition().x > this->worldRightLimit - 16.0f)
    {
        this->setPosition(this->worldRightLimit - 16.0f, -1.0f);
    }

    if (this->getPosition().y < this->worldUpLimit)
    {
        this->setPosition(-1.0f, this->worldUpLimit);
    }

    if (this->getPosition().y > this->worldDownLimit - 22.0f)
    {
        this->setPosition(-1.0f, this->worldDownLimit - 22.0f);
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

void Player::setMapLimits(int limits[2])
{
    this->worldRightLimit = limits[1] * this->cellSize;
    this->worldDownLimit = limits[0] * this->cellSize;
}

Player::Player(int startGraphX, int startGraphY)
{
    this->setHealthPoints(5);
    this->graphX = startGraphX;
    this->graphY = startGraphY;
    this->setPosition(this->graphX * this->cellSize, this->graphY * this->cellSize);
    this->currentSpriteSheet = movingDownSprite;
}




