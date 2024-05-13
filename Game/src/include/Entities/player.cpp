#include "player.h"

void Player::movePlayer(float frameTime, int mapSize[2]) {
    if (!IsKeyDown(KEY_LEFT) && !IsKeyDown(KEY_RIGHT) && !IsKeyDown(KEY_UP) && !IsKeyDown(KEY_DOWN))
    {
        // Stop movement
    }

    if (IsKeyDown(KEY_UP))
    {
        this->move(frameTime, Entity::mvUp);
        this->currentSpriteSheet = movingUpSprite;
    }

    if (IsKeyDown(KEY_DOWN))
    {
        this->move(frameTime, Entity::mvDown);
        this->currentSpriteSheet = movingDownSprite;
    }

    if (IsKeyDown(KEY_LEFT))
    {
        this->move(frameTime, Entity::mvLeft);
        this->currentSpriteSheet = movingLeftSprite;
    }

    if (IsKeyDown(KEY_RIGHT))
    {
        this->move(frameTime, Entity::mvRight);
        this->currentSpriteSheet = movingRightSprite;
    }

    if (this->getPosition().x < this->leftLimit) {
        this->setPosition(this->leftLimit, -1.0f);
    }

    if (this->getPosition().x > this->rightLimit - 16.0f) {
        this->setPosition(this->rightLimit - 16.0f, -1.0f);
    }

    if (this->getPosition().y < this->upLimit) {
        this->setPosition(-1.0f, this->upLimit);
    }

    if (this->getPosition().y > this->downLimit - 22.0f) {
        this->setPosition(-1.0f, this->downLimit - 22.0f);
    }
}

void Player::setMapCellSize(int currentMapCellSize) {
    this->cellSize = currentMapCellSize;
}

void Player::setMapLimits(int limits[2]) {
    this->rightLimit = limits[1] * this->cellSize;
    this->downLimit = limits[0] * this->cellSize;
}

Player::Player(float xCord, float yCord, int currentMapCellSize) {
    this->setMapCellSize(currentMapCellSize);   
    this->setHealthPoints(5);
    this->setPosition(xCord, yCord);
    this->currentSpriteSheet = movingDownSprite;
}
