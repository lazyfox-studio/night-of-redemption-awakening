#include "../Headers/Unit.h"
#include <iostream>
float Unit::getX()
{
	return x;
}

float Unit::getY()
{
	return y;
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