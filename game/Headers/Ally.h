#pragma once
#include <SFML/Graphics.hpp>

extern sf::RenderWindow window;
extern sf::View view;

class Ally
{
    friend class Enemy;
protected:
    float x;
    float y;
    int health;

public:
    Ally()
    {

    }
	Ally(float _x, float _y, int _health) : x(_x), y(_y), health(_health)
	{

	}
    ~Ally()
    {

    }

    virtual void draw() = 0;
	virtual void move_(float, float, bool = false) = 0;
};