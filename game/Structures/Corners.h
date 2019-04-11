#pragma once
#include "Screen.h"
#include "../Headers/Allies/Player.h"

struct CornerPoint
{
	float x;
	float y;
};

struct Corners
{
	CornerPoint top_left;
	CornerPoint top_right;
	CornerPoint bottom_left;
	CornerPoint bottom_right;

	void calculate(const ScreenResolution* screen, Player* player)
	{
		float player_x = player->getX(), player_y = player->getY();
		float half_screen_w = float(screen->w) / 2.f, half_screen_h = float(screen->h) / 2.f;
		top_left.x     = player_x - half_screen_w;
		top_left.y     = player_y - half_screen_h;
		top_right.x    = player_x + half_screen_w;
		top_right.y    = player_y - half_screen_h;
		bottom_left.x  = player_x - half_screen_w;
		bottom_left.y  = player_y + half_screen_h;
		bottom_right.x = player_x + half_screen_w;
		bottom_right.y = player_y + half_screen_h;
	};
};
Corners corners;