#pragma once
#include "../../Utilities/Screen.h"
#include "../Ally.h"

class Person : public Ally
{

public:
    Person() : Ally(100, 100, 200, 3.0f, 0.0f)
    {
		texture.loadFromFile("Textures/player.png");
		texture.setSmooth(true);
		sprite.setTexture(texture);
		sprite.setOrigin(sf::Vector2f(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f));
		sprite.setPosition((float)screen.w / 2, (float)screen.h / 2);
    }

    ~Person()
    {
    }

    void shoot();
    void draw();
	void move(float, float, bool = false);
};
