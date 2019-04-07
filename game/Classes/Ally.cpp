#include "../Headers/Ally.h"

Ally::Ally()
{
}

Ally::Ally(float _x, float _y, int _health, float _speed, int _pov) :
	Unit(_x, _y, _health, _speed, _pov) 
{

}

Ally::~Ally()
{
}
