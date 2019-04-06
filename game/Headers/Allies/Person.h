#pragma once
#include "../../Utilities/Screen.h"
#include "../Ally.h"
#include "../Enemy.h"

class Person : public Ally
{

public:
	Person();
	~Person();

    void shoot(List<Enemy>& enemies);
	void move(float, float, bool = false);
};
