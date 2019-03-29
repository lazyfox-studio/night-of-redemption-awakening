#pragma once
#include "../definitions.h"
 
class Ally
{
    friend class Enemy;
protected:
    float x;
    float y;
    int health;

public:
    Ally()
    {

    }
    ~Ally()
    {

    }

    virtual void draw() = 0;
};