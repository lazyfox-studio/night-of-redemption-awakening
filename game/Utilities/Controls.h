#pragma once
#include "../Headers/Ally.h"

struct KeyboardControl
{
	bool W = false;
	bool A = false;
	bool S = false;
	bool D = false;
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
		player->move_(0.f, -1.0f, Kb.LShift);
	}
	if (Kb.A)
	{
		player->move_(-1.f, 0.f, Kb.LShift);
	}
	if (Kb.S)
	{
		player->move_(0.f, 1.0f, Kb.LShift);
	}
	if (Kb.D)
	{
		player->move_(1.0f, 0.0f, Kb.LShift);
	}
}