#include "../Headers/Unit.h"

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
	return (x + dx <= 0) || (x + dx >= screen.w) || (y + dy <= 0) || (y + dy >= screen.h);
}