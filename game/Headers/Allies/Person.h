#pragma once
#include "../Ally.h"

class Person : Ally
{
    float speed;
    float pov; //Направление взгляда

public:
    Person()
    {

    }
    ~Person()
    {

    }

    void move(float x, float y);
    void shoot();
    void draw();
};
