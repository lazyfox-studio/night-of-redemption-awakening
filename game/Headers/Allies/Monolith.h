#pragma once
#include "../Ally.h"

class Monolith : public Ally
{

public:
    Monolith() : Ally((float)screen.w / 2.0f, (float)screen.h / 2.0f, 200, 0.0f, 0.0f)
    {
        texture->loadFromFile("Textures/monolith.png");
        texture->setSmooth(true);
        sprite.setTexture(*texture);
        sprite.setTextureRect(sf::IntRect(0, 0, SPRITE_SIZE, SPRITE_SIZE));
        sprite.setOrigin(sf::Vector2f(SPRITE_SIZE / 2.0f, SPRITE_SIZE / 2.0f));
        sprite.setPosition(x, y);
    }
    ~Monolith()
    {

    }

	void move(float, float, bool = false);
};