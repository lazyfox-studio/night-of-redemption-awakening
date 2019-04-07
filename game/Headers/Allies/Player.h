#pragma once
#include "../../Utilities/Screen.h"
#include "../Ally.h"
#include "../Enemy.h"
#include <windows.h>

class Player : public Ally
{
	int damage;

public:
	Player();
	~Player();

    void shoot(List<Enemy>& enemies);
	void move(float, float, bool = false);

	void test_ani();
};
