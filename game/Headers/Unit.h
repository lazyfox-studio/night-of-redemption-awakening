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
	Unit(float, float);
	Unit(float, float, int, float, float);
	~Unit();

	float getX();
	float getY(); 

	void setX(float);
	void setY(float);

	void draw();
	void rotate(float);
	void rotate_to(float);
	bool is_out_of_terrain(float, float);
	bool is_edge_of_terrain(float, float);
};