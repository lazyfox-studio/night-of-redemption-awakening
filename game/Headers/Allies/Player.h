#pragma once
#include "../../Structures/Screen.h"
#include "../Ally.h"
#include "../Enemy.h"
#include <windows.h>

#define MAX_STAMINA 120

class Player : public Ally
{
	int damage;
    int ammo;
    int stamina;
public:
	Player();
	~Player();

    void shoot(List<Enemy>& enemies);
    void reload();
	void move(float, float, bool = false);

	int get_ammo();
	void test_ani();
};
