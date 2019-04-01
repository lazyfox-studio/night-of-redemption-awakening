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
	//int bitmask = 0;
	if (Kb.W)
	{
		//bitmask |= 1;
		player->move(0.f, -1.0f, Kb.LShift);
	}
	if (Kb.A)
	{
		//bitmask |= 4;
		player->move(-1.f, 0.f, Kb.LShift);
	}
	if (Kb.S)
	{
		//bitmask |= 2;
		player->move(0.f, 1.0f, Kb.LShift);
	}
	if (Kb.D)
	{
		//bitmask |= 8;
		player->move(1.0f, 0.0f, Kb.LShift);
	}
	/*if (!bitmask)
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
	}*/

    sf::Vector2i mouse = sf::Mouse::getPosition(window);
    int deg = 0;
    if ((3 * mouse.x + 16 * mouse.y - 7680) < 0)
    {
        if ((-9 * mouse.x + 8 * mouse.y + 2860) < 0)
        {
            if ((9 * mouse.x + 8 * mouse.y - 8640) < 0)
            {
                deg = 0;
            }
            else
            {
                deg = 45;
            }
        }
        else
        {
            if ((-3 * mouse.x + 16 * mouse.y - 3840) < 0)
            {
                deg = -45;
            }
            else
            {
                deg = -90;
            }
        }
    }
    else
    {
        if ((-9 * mouse.x + 8 * mouse.y + 2860) < 0)
        {
            if ((-3 * mouse.x + 16 * mouse.y - 3840) < 0)
            {
                deg = 90;
            }
            else
            {
                deg = 135;
            }
        }
        else
        {
            if ((9 * mouse.x + 8 * mouse.y - 8640) < 0)
            {
                deg = -135;
            }
            else
            {
                deg = 180;
            }
        }
    }
	player->rotate_to((float)deg);
}

inline void draw_all(Unit* units[], int count)
{
	for (int i = 0; i < count; i++)
		units[i]->draw();
}