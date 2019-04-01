#pragma once
#include "../Utilities/Screen.h"
#include <SFML/Graphics.hpp>

extern sf::RenderWindow window;
extern sf::View view;

class Unit
{
protected:
	float x;
	float y;
	int health;
	float speed;
	float pov;

	sf::Texture texture;
	sf::Sprite sprite;

public:
	Unit()
	{
	}

	Unit(float _x, float _y, int _health, float _speed, float _pov) : 
		x(_x), y(_y), health(_health), speed(_speed), pov(_pov) {}

	~Unit()
	{
	}

	virtual void draw() = 0;
	void rotate(float);
	void rotate_to(float);
	bool is_out_of_terrain(float, float);
	virtual void move(float, float, bool = false) = 0;
};