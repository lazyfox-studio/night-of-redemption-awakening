#pragma once

struct ScreenResolution
{
	int w = 1280;
	int h = 720;
};
const ScreenResolution screen;

struct MapSize
{
	float w = 6400.f;
	float h = 3600.f;
	float padding_x = 640.f;
	float padding_y = 360.f;
};
const MapSize map;