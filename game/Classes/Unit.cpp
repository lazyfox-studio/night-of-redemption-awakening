#include "../Headers/Unit.h"
#include <iostream>

Unit::Unit() : x(0), y(0), health(0), speed(0), pov(0), texture(new sf::Texture) 
{
	setX(x);
	setY(y);
}

Unit::Unit(float _x, float _y) : x(_x), y(_y), health(0), speed(0), pov(0), texture(new sf::Texture)
{
	setX(x);
	setY(y);
}

Unit::Unit(float _x, float _y, int _health, float _speed, float _pov) :
	x(_x), y(_y), health(_health), speed(_speed), pov(_pov), texture(new sf::Texture)
{
	setX(x);
	setY(y);
}

float Unit::getX()
{
	return x;
}

float Unit::getY()
{
	return y;
}

void Unit::setX(float _x)
{
	sprite.setPosition(_x, y);
	x = _x;
}

void Unit::setY(float _y)
{
	sprite.setPosition(x, _y);
	y = _y;
}

void Unit::draw()
{
    window.draw(sprite);
}

void Unit::rotate(float deg)
{
	sprite.rotate(deg);
	pov += deg;
}

void Unit::rotate_to(float deg)
{
	sprite.setRotation(deg);
	pov = deg;
}

bool Unit::is_out_of_terrain(float dx, float dy)
{
	return (x + dx < screen.w / 2) || (x + dx > screen.w * 1.5) || (y + dy < screen.h / 2) || (y + dy > screen.h * 1.5);
}