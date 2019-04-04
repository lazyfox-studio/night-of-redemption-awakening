#pragma once
#include "../Utilities/Screen.h"
#include <SFML/Graphics.hpp>

#define SPRITE_SIZE 64

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

	sf::Texture *texture;
	sf::Sprite sprite;

public:
	Unit();
	Unit(float _x, float _y);
	Unit(float _x, float _y, int _health, float _speed, float _pov);

	~Unit()
	{
	}

	float getX();
	float getY(); 

	void setX(float);
	void setY(float);

	void draw();
	void rotate(float);
	void rotate_to(float);
	bool is_out_of_terrain(float, float);
};