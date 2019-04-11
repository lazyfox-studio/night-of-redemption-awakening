#pragma once
#include "../Ally.h"

class Monolith : public Ally
{

public:
	Monolith();
	~Monolith();

	void move(float dbx, float dby, List<Unit>& units, bool is_shift);
};