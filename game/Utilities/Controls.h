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
		player->rotate_to(0);
	}
	if (Kb.A)
	{
		player->move(-1.f, 0.f, Kb.LShift);
		player->rotate_to(270);
	}
	if (Kb.S)
	{
		player->move(0.f, 1.0f, Kb.LShift);
		player->rotate_to(180);
	}
	if (Kb.D)
	{
		player->move(1.0f, 0.0f, Kb.LShift);
		player->rotate_to(90);
	}
	if (Kb.Q)
	{
		player->rotate(-1.0f);
	}
	if (Kb.E)
	{
		player->rotate(1.0f);
	}
}

inline void draw_all(Unit* units[], int count)
{
	for (int i = 0; i < count; i++)
		units[i]->draw();
}