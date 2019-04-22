#include "../Headers/Unit.h"
#include <iostream>

Unit::Unit() : x(0), y(0), health(0), speed(0), pov(0)
{
	sprite.set_origin(0.5f, 0.5f);
	setX(x);
	setY(y);
	move_flood_control[0] = move_flood_control[1] = 0;
	attack_flood_control[0] = attack_flood_control[1] = attacking = 0;
}

Unit::Unit(float _x, float _y) : x(_x), y(_y), health(0), speed(0), pov(0)
{
	sprite.set_origin(0.5f, 0.5f);
	setX(x);
	setY(y);
	move_flood_control[0] = move_flood_control[1] = 0;
	attack_flood_control[0] = attack_flood_control[1] = attacking = 0;
}

Unit::Unit(float _x, float _y, int _health, float _speed, int _pov) :
	x(_x), y(_y), health(_health), speed(_speed), pov(_pov)
{
	sprite.set_origin(0.5f, 0.5f);
	setX(x);
	setY(y);
	move_flood_control[0] = move_flood_control[1] = 0;
	attack_flood_control[0] = attack_flood_control[1] = attacking = 0;
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
	sprite.set_position(_x, y);
	x = _x;
}

void Unit::setY(float _y)
{
	sprite.set_position(x, _y);
	y = _y;
}

bool Unit::is_ally()
{
	return false;
}

bool Unit::is_enemy()
{
	return false;
}

void Unit::damage_cooldown_update()
{
    if (damage_cooldown > 0) damage_cooldown--;
}

void Unit::draw()
{
	sprite.draw_in(window);
}

void Unit::rotate(int deg)
{
	sprite.rotate(float(deg));
	pov += deg;
}

void Unit::rotate_to(int deg)
{
	sprite.set_rotation(float(deg));
	pov = deg;
}

// здесь хрень, надо будет потом переписать
bool Unit::is_out_of_terrain(float dx, float dy)
{
	return (x + dx < 0) || (x + dx > map.w) || (y + dy < 0) || (y + dy > map.h);
}
