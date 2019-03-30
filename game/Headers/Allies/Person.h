#pragma once
#include "../Ally.h"

class Person : public Ally
{
    float speed;
    float pov; //Направление взгляда

public:
    Person() : Ally(100, 100, 200), speed(10), pov(0)
    {
    }
    ~Person()
    {

    }

    //Движение персонажа, для первых двух значений передавать -1 0 1, для shift 0 1
    void move();
    void shoot();
    void draw();

	void move_(float, float, bool = false);
};
