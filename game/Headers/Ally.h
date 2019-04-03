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

	Ally(float _x, float _y, int _health, float _speed, float _pov) : 
		Unit(_x, _y, _health, _speed, _pov) {}

    ~Ally()
    {

    }
	virtual void move(float, float, bool = false) = 0;
};