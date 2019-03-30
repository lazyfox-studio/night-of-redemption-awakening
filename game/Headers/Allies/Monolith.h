#pragma once
#include "../Ally.h"

class Monolith : Ally
{

public:
    Monolith()
    {

    }
    ~Monolith()
    {

    }

    void draw();
	void move_(float, float, bool = false);
};