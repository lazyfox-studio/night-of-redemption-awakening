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
    Person() : Ally(100, 100, 200), speed(3.0f), pov(0.0f)
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

    //Движение персонажа, для первых двух значений передавать -1 0 1, для shift 0 1
    void move_d();
    void shoot();
    void draw();
	void rotate(float);
	void rotate_to(float);
	void move(float, float, bool = false);

	bool is_out_of_terrain(float, float);
};
