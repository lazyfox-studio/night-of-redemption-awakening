#pragma once
#include "../../Utilities/Screen.h"
#include "../Ally.h"
#include "../Enemy.h"
#include <windows.h>

class Player : public Ally
{
	int damage;
    int ammo;
public:
	Player();
	~Player();

    void shoot(List<Enemy>& enemies);
    void reload();
	void move(float, float, bool = false);

	int get_ammo();
	void test_ani();
};
