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
	int bitmask = 0;
	if (Kb.W)
	{
		bitmask |= 1;
		player->move(0.f, -1.0f, Kb.LShift);
	}
	if (Kb.A)
	{
		bitmask |= 4;
		player->move(-1.f, 0.f, Kb.LShift);
	}
	if (Kb.S)
	{
		bitmask |= 2;
		player->move(0.f, 1.0f, Kb.LShift);
	}
	if (Kb.E)
	{
		player->rotate(45.0f);
	}
	if (!bitmask)
		return;
	int deg = 0;
	switch (bitmask)
	{
	case 1:
		deg = 0;
		break;
	case 2:
		deg = 180;
		break;
	case 4:
		deg = 270;
		break;
	case 8:
		deg = 90;
		break;
	case 5:
		deg = 315;
		break;
	case 9:
		deg = 45;
		break;
	case 6:
		deg = 225;
		break;
	case 10:
		deg = 135;
		break;
	}
	player->rotate_to((float)deg);
}

inline void draw_all(Unit* units[], int count)
{
	for (int i = 0; i < count; i++)
		units[i]->draw();
}