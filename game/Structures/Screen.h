#pragma once

struct Screen
{
	static int w;
	static int h;
};

struct MapSize
{
	float w = 4800.f;
	float h = 2700.f;
	float padding_x = 960.f;
	float padding_y = 540.f;
};
const MapSize map;

struct CameraOffset
{
	float x = 0.f;
	float y = 0.f;
};