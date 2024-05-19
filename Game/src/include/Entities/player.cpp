#include "player.h"

void Player::move(float frameTime, const char dir)
{
    above = &this->currentMap->get(graphAbove, graphX);
    below = &this->currentMap->get(graphBelow, graphX);
    left = &this->currentMap->get(graphY, graphLeft);
    right = &this->currentMap->get(graphY, graphRight);
    
    if (dir == mvUp)
    {
        if(above->chunk_type == wall && this->getPosition().y < this->aboveLimit + 3.0f)
        {
            this->setPosition(-1.0f, aboveLimit);
        } else 
        {
            this->position.y -= entityVerticalSpeed * frameTime;
        }
    }

    if (dir == mvDown) 
    {
        if(below->chunk_type == wall && this->getPosition().y > this->belowLimit - 3.0f)
        {
            this->setPosition(-1.0f, belowLimit);
        } else 
        {
            this->position.y += entityVerticalSpeed * frameTime;
        }
    }

    if (dir == mvLeft)
    {
        if(left->chunk_type == wall && this->getPosition().x < this->leftLimit + 3.0f)
        {
            this->setPosition(leftLimit, -1.0f);
        } else 
        {
            this->position.x -= entityHorizontalSpeed * frameTime;
        }
    }

    if (dir == mvRight)
    {
        if(right->chunk_type == wall && this->getPosition().x > this->rightLimit - 3.0f)
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
    if (!IsKeyDown(KEY_LEFT) && !IsKeyDown(KEY_RIGHT) && !IsKeyDown(KEY_UP) && !IsKeyDown(KEY_DOWN))
    {
        this->isMoving = false;
    }

    if (IsKeyDown(KEY_UP))
    {
        this->move(frameTime, Entity::mvUp);
        this->currentSpriteSheet = movingUpSprite;
        this->isMoving = true;
    }

    if (IsKeyDown(KEY_DOWN))
    {
        this->move(frameTime, Entity::mvDown);
        this->currentSpriteSheet = movingDownSprite;
        this->isMoving = true;
    }

    if (IsKeyDown(KEY_LEFT))
    {
        this->move(frameTime, Entity::mvLeft);
        this->currentSpriteSheet = movingLeftSprite;
        this->isMoving = true;
    }

    if (IsKeyDown(KEY_RIGHT))
    {
        this->move(frameTime, Entity::mvRight);
        this->currentSpriteSheet = movingRightSprite;
        this->isMoving = true;
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
