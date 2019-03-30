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

inline void move_all(Ally** allies, int allies_n)
{
	if (Kb.W)
	{
		for (int i = 0; i < allies_n; i++)
			allies[i]->move_(0.f, -1.0f, Kb.LShift);
	}
	if (Kb.A)
	{
		for (int i = 0; i < allies_n; i++)
			allies[i]->move_(-1.f, 0.f, Kb.LShift);
	}
	if (Kb.S)
	{
		for (int i = 0; i < allies_n; i++)
			allies[i]->move_(0.f, 1.0f, Kb.LShift);
	}
	if (Kb.D)
	{
		for (int i = 0; i < allies_n; i++)
			allies[i]->move_(1.0f, 0.0f, Kb.LShift);
	}
}