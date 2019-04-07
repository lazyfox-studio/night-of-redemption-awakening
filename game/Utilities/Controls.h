#pragma once
#include "../Headers/Unit.h"
#include "Screen.h"
#include "List.h"

struct KeyboardControl
{
	bool W = false;
	bool A = false;
	bool S = false;
	bool D = false;
	bool Q = false;
	bool E = false;
	bool LShift = false;
};
KeyboardControl Kb;

struct MouseControl
{
	bool Left   = false;
	bool Right  = false;
	bool Middle = false;

	float x;
	float y;

	unsigned long long flood_control = 0;
};
MouseControl Mouse;

struct CameraOffset
{
	float x;
	float y;
};

struct Precalculated
{
	float c1, c2, c3, c4, c5, c6, c7, c8;
};
Precalculated c_coefficients;

int GCD(int n1, int n2)
{
	int rem;
	if (n1 < n2)
	{
		int tmp = n1;
		n1 = n2;
		n2 = tmp;
	}
	while (rem = n1 % n2)
	{
		n1 = n2;
		n2 = rem;
	}
	return n2;
}

void calculate_coefficients(Precalculated& coef, const ScreenResolution& screen)
{
	int gcd = GCD(screen.w, screen.h);
	c_coefficients.c1 = (float)screen.w / (float)gcd; // 16
	c_coefficients.c2 = (float)screen.h / (float)gcd; // 9
	c_coefficients.c3 = c_coefficients.c1 / 2.0f; // 8
	c_coefficients.c4 = c_coefficients.c2 / 3.0f; // 3
	c_coefficients.c5 = (float)screen.w * 6.0f; // 7680
	c_coefficients.c6 = c_coefficients.c1 * 178.75f; // 2860
	c_coefficients.c7 = (float)screen.h * 12.0f; // 8640
	c_coefficients.c8 = (float)screen.w * c_coefficients.c4; // 3840
}

inline void control_player(Player* player, List<Enemy>& enemies)
{
	// Moving
	float dx = 0.0f, dy = 0.0f;
	if (Kb.W)
		dy -= 1.0f;
	if (Kb.A)
		dx -= 1.0f;
	if (Kb.S)
		dy += 1.0f;
	if (Kb.D)
		dx += 1.0f;
	player->move(dx, dy, Kb.LShift);

	// Shooting
    if (Mouse.Left)
    {
        player->shoot(enemies);
    }

	// Rotating
    int deg = 0;
    if ((c_coefficients.c4 * Mouse.x + c_coefficients.c1 * Mouse.y - c_coefficients.c5) < 0)
        if ((-(c_coefficients.c2) * Mouse.x + c_coefficients.c3 * Mouse.y + c_coefficients.c6) < 0)
            if ((c_coefficients.c2 * Mouse.x + c_coefficients.c3 * Mouse.y - c_coefficients.c7) < 0)
                deg = 0;
            else
                deg = 45;
        else
            if ((-(c_coefficients.c4) * Mouse.x + c_coefficients.c1 * Mouse.y - c_coefficients.c8) < 0)
                deg = -45;
            else
                deg = -90;
    else
        if ((-(c_coefficients.c2) * Mouse.x + c_coefficients.c3 * Mouse.y + c_coefficients.c6) < 0)
            if ((-(c_coefficients.c4) * Mouse.x + c_coefficients.c1 * Mouse.y - c_coefficients.c8) < 0)
                deg = 90;
            else
                deg = 135;
        else
            if ((c_coefficients.c2 * Mouse.x + c_coefficients.c3 * Mouse.y - c_coefficients.c7) < 0)
                deg = -135;
            else
                deg = 180;
	player->rotate_to(deg);
}

inline void draw_all(List<Unit>& units)
{
	units.foreach(&(Unit::draw));
}

inline void check_focus_enemies(List<Enemy>& enemies, List<Ally>& allies)
{
    for (ListItem<Enemy>* i = enemies.head; i; i = i->next)
        i->value->focus_change(allies);
}

inline void check_range_enemies(List<Enemy>& enemies)
{
    enemies.foreach(&(Enemy::range));
}

inline void move_enemies(List<Enemy>& enemies)
{
    enemies.foreach(&(Enemy::move));
}

bool unit_died(Unit* unit)
{
	return unit->get_health() <= 0;
}

inline void kill_dead(List<Unit>& units)
{
	units.remove_if(unit_died);
}