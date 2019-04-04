#pragma once
#include "../../Utilities/Screen.h"
#include "../Ally.h"

class Person : public Ally
{

public:
	Person();
	~Person();

    void shoot();
	void move(float, float, bool = false);
};
