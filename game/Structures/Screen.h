#pragma once

struct ScreenResolution
{
	int w = 1280;
	int h = 720;
};
const ScreenResolution screen;

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