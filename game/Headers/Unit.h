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
	int pov;

	sf::Texture *texture;
	sf::Sprite sprite;

public:
	Unit();
	Unit(float, float);
	Unit(float, float, int, float, int);
	~Unit();

	float getX();
	float getY();
    int get_health();

	void setX(float);
	void setY(float);

	void draw();
	void rotate(int);
	void rotate_to(int);
	bool is_out_of_terrain(float, float);
	bool is_edge_of_terrain(float, float);
};