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

    //Движение персонажа, для первых двух значений передавать -1 0 1, для shift 0 1
    void move(int dx, int dy, int shift);
    void shoot();
    void draw();
};
