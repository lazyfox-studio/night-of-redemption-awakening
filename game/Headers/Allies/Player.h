#pragma once
#include "../../Utilities/Screen.h"
#include "../Ally.h"
#include "../Enemy.h"

class Player : public Ally
{

public:
	Player();
	~Player();

    void shoot(List<Enemy>& enemies);
	void move(float, float, bool = false);
};
