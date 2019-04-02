#pragma once
#include "../Headers/Unit.h"
#include "Screen.h"

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

inline void move_all(Person* player)
{
	if (Kb.W)
	{
		player->move(0.f, -1.0f, Kb.LShift);
	}
	if (Kb.A)
	{
		player->move(-1.f, 0.f, Kb.LShift);
	}
	if (Kb.S)
	{
		player->move(0.f, 1.0f, Kb.LShift);
	}
	if (Kb.D)
	{
		player->move(1.0f, 0.0f, Kb.LShift);
	}

    sf::Vector2i mouse = sf::Mouse::getPosition(window);
    int deg = 0;
    if ((c_coefficients.c4 * mouse.x + c_coefficients.c1 * mouse.y - c_coefficients.c5) < 0)
        if ((-(c_coefficients.c2) * mouse.x + c_coefficients.c3 * mouse.y + c_coefficients.c6) < 0)
            if ((c_coefficients.c2 * mouse.x + c_coefficients.c3 * mouse.y - c_coefficients.c7) < 0)
                deg = 0;
            else
                deg = 45;
        else
            if ((-(c_coefficients.c4) * mouse.x + c_coefficients.c1 * mouse.y - c_coefficients.c8) < 0)
                deg = -45;
            else
                deg = -90;
    else
        if ((-(c_coefficients.c2) * mouse.x + c_coefficients.c3 * mouse.y + c_coefficients.c6) < 0)
            if ((-(c_coefficients.c4) * mouse.x + c_coefficients.c1 * mouse.y - c_coefficients.c8) < 0)
                deg = 90;
            else
                deg = 135;
        else
            if ((c_coefficients.c2 * mouse.x + c_coefficients.c3 * mouse.y - c_coefficients.c7) < 0)
                deg = -135;
            else
                deg = 180;

	player->rotate_to((float)deg);
}

inline void draw_all(Unit* units[], int count)
{
	for (int i = 0; i < count; i++)
		units[i]->draw();
}