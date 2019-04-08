#pragma once
#include "Unit.h"
#include "../Utilities/List.h"

class Ally : public Unit
{
    friend class Enemy;
public:
	Ally();
	Ally(float, float, int, float, int);
	~Ally();

	bool is_ally();
	virtual void move(float, float, bool = false) = 0;
};