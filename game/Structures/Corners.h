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
	static CornerPoint top_left;
	static CornerPoint top_right;
	static CornerPoint bottom_left;
	static CornerPoint bottom_right;

	static void calculate(Player* player)
	{
		float player_x = player->getX(), player_y = player->getY();
		float half_screen_w = float(Screen::w) / 2.f, half_screen_h = float(Screen::h) / 2.f;
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