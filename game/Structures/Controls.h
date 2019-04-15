#pragma once

struct KeyboardControl
{
	bool W = false;
	bool A = false;
	bool S = false;
	bool D = false;
	bool Q = false;
	bool E = false;
	bool R = false;
	bool LShift = false;
};
KeyboardControl Kb;

struct MouseControl
{
	bool Left = false;
	bool Right = false;
	bool Middle = false;

	float x;
	float y;

	unsigned long long flood_control[2] = { 0 };
};
MouseControl Mouse;