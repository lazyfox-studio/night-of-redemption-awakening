#pragma once
#include "../../Utilities/Screen.h"
#include "../Ally.h"

class Person : public Ally
{

public:
    Person() : Ally((float)screen.w / 2.0f, (float)screen.h / 2.0f, 200, 3.0f, 0.0f)
    {
		texture.loadFromFile("Textures/player.png");
		texture.setSmooth(true);
		sprite.setTexture(texture);
		sprite.setOrigin(sf::Vector2f(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f));
		sprite.setPosition(x, y);
    }

    ~Person()
    {
    }

    void shoot();
    void draw();
	void move(float, float, bool = false);
};
