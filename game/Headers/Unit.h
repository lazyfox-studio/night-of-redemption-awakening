#pragma once
#include <SFML/Graphics.hpp>

extern sf::RenderWindow window;
extern sf::View view;

class Unit
{
protected:
	float x;
	float y;
	int health;

public:
	Unit()
	{

	}
	Unit(float _x, float _y, int _health) : x(_x), y(_y), health(_health)
	{

	}
	~Unit()
	{

	}
	virtual void draw() = 0;
};