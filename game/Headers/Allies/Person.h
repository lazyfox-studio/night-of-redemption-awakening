#pragma once
#include "../../Utilities/Screen.h"
#include "../Ally.h"

class Person : public Ally
{
    float speed;
    float pov; //Направление взгляда

	sf::Texture texture;
	sf::Sprite sprite;

public:
    Person() : Ally(100, 100, 200), speed(3), pov(0)
    {
		texture.loadFromFile("Textures/player.png");
		sprite.setTexture(texture);
		sprite.setPosition((float)screen.w / 2, (float)screen.h / 2);
    }
    ~Person()
    {

    }

    //Движение персонажа, для первых двух значений передавать -1 0 1, для shift 0 1
    void move();
    void shoot();
    void draw();

	void move_(float, float, bool = false);

	bool is_out_of_terrain(float, float);
};
