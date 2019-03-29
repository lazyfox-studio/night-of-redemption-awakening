#pragma once
#include "../Ally.h"

class Person : Ally
{
    float speed;
    float pov; //Направление взгляда

public:
    Person()
    {
        x = 100;
        y = 100;
        health = 200;
        speed = 5;
        pov = 0;
    }
    ~Person()
    {

    }

    //Движение персонажа, для первых двух значений передавать -1 0 1, для shift 0 1
    void move(int dx, int dy, int shift);
    void shoot();
    void draw();
};
