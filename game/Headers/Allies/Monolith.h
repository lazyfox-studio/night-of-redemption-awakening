#pragma once
#include "../Ally.h"

class Monolith : public Ally
{

public:
	Monolith();
	~Monolith();

	void move(float, float, bool = false);
};