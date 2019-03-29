#pragma once
 
class Ally
{
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