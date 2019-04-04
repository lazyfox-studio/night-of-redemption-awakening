#pragma once
#include "Unit.h"
#include "../Utilities/List.h"

class Ally : public Unit
{
    friend class Enemy;
public:
	Ally();
	Ally(float, float, int, float, float);
	~Ally();

	virtual void move(float, float, bool = false) = 0;
};