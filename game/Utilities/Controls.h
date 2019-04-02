#pragma once
#include "../Headers/Unit.h"

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
    if ((3 * mouse.x + 16 * mouse.y - 7680) < 0)
        if ((-9 * mouse.x + 8 * mouse.y + 2860) < 0)
            if ((9 * mouse.x + 8 * mouse.y - 8640) < 0)
                deg = 0;
            else
                deg = 45;
        else
            if ((-3 * mouse.x + 16 * mouse.y - 3840) < 0)
                deg = -45;
            else
                deg = -90;
    else
        if ((-9 * mouse.x + 8 * mouse.y + 2860) < 0)
            if ((-3 * mouse.x + 16 * mouse.y - 3840) < 0)
                deg = 90;
            else
                deg = 135;
        else
            if ((9 * mouse.x + 8 * mouse.y - 8640) < 0)
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