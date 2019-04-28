#pragma once

struct Keyboard
{
	static bool W;
	static bool A;
	static bool S;
	static bool D;
	static bool Q;
	static bool E;
	static bool R;
	static bool LShift;
	static bool Escape;
};

struct Mouse
{
	static bool Left;
	static bool Right;
	static bool Middle;

	static float x;
	static float y;

	static unsigned long long flood_control[2];
};