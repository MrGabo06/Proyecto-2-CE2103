#include "raylib.h"

#define entityVerticalSpeed 200.0f
#define entityHorizontalSpeed 200.0f

class Entity
{
private:
    //Attributes
    Vector2 position;
    int healthPoints = 0;

public:
    //Attributes
    const char mvUp = 'U';
    const char mvDown = 'D';
    const char mvLeft = 'L';
    const char mvRight = 'R';

    //Methods
    void move(float frameTime, const char dir)
    {
        if (dir == mvUp)
        {
            this->position.y -= entityVerticalSpeed * frameTime;
        }

        if (dir == mvDown) 
        {
            this->position.y += entityVerticalSpeed * frameTime;
        }

        if (dir == mvLeft)
        {
            this->position.x -= entityHorizontalSpeed * frameTime;
        }

        if (dir == mvRight)
        {
            this->position.x += entityHorizontalSpeed * frameTime;
        }
    }

    Vector2 getPosition()
    {
        return position;
    }

    void setHealthPoints(int newHp)
    {
        healthPoints = newHp;
    }

    void setPosition(float xCords, float yCords)
    {
        position.x = xCords;
        position.y = yCords;
    }
};