#pragma once
 
class Ally
{
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