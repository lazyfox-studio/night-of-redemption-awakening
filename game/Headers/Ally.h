#pragma once
#include "Unit.h"

class Ally : public Unit
{
    friend class Enemy;
protected:


public:
    Ally()
    {

    }
	Ally(float _x, float _y, int _health) : Unit(_x, _y, _health)
	{

	}
    ~Ally()
    {

    }

    virtual void draw() = 0;
	virtual void move(float, float, bool = false) = 0;
};