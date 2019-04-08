#include "../Headers/Unit.h"
#include <iostream>

Unit::Unit() : x(0), y(0), health(0), speed(0), pov(0), texture(new sf::Texture) 
{
	sprite.setOrigin(sf::Vector2f(0.5f, 0.5f));
	setX(x);
	setY(y);
}

Unit::Unit(float _x, float _y) : x(_x), y(_y), health(0), speed(0), pov(0), texture(new sf::Texture)
{
	sprite.setOrigin(sf::Vector2f(0.5f, 0.5f));
	setX(x);
	setY(y);
}

Unit::Unit(float _x, float _y, int _health, float _speed, int _pov) :
	x(_x), y(_y), health(_health), speed(_speed), pov(_pov), texture(new sf::Texture)
{
	sprite.setOrigin(sf::Vector2f(0.5f, 0.5f));
	setX(x);
	setY(y);
}

Unit::~Unit()
{
}

float Unit::getX()
{
	return x;
}

float Unit::getY()
{
	return y;
}

int Unit::get_health()
{
    return health;
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

void Unit::rotate(int deg)
{
	sprite.rotate(float(deg));
	pov += deg;
}

void Unit::rotate_to(int deg)
{
	sprite.setRotation(float(deg));
	pov = deg;
}

// ����� �����, ���� ����� ����� ����������
bool Unit::is_out_of_terrain(float dx, float dy)
{
	return (x + dx < 0) || (x + dx > map.w) || (y + dy < 0) || (y + dy > map.h);
}

bool Unit::is_edge_of_terrain(float dx, float dy)
{
	const float edge = 360.f;
	const float delta = 280.f; // ����� ������� ����
	return (x + dx < edge + delta) || (x + dx > map.w - edge - delta) || (y + dy < edge) || (y + dy > map.h - edge);
}
