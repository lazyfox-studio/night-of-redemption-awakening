#pragma once
#include "../Structures/Screen.h"
#include "MSprite.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#define SPRITE_SIZE 200
#define UNIT_SIZE 96
#define AK74_ATTAK_SPEED 6
#define AK74_RELOAD_TIME 180
#define AK74_MAGASINE 100

extern sf::RenderWindow window;
extern sf::View view;
extern sf::Sound sound;

class Unit
{
protected:
	float x;
	float y;
	int health;
	float speed;
	int pov;
    int damage_cooldown = 0; //Ограничение на скорость атак

	unsigned move_flood_control[2];
	unsigned attack_flood_control[2];
	bool attacking;

	MSprite sprite;

public:
	Unit();
	Unit(float, float);
	Unit(float, float, int, float, int);
	~Unit();

	float getX();
	float getY();
    int get_health();

	void setX(float);
	void setY(float);

	virtual bool is_ally();
	virtual bool is_enemy();

    void damage_cooldown_update();

	virtual void draw();
	void rotate(int);
	void rotate_to(int);
	bool is_out_of_terrain(float, float);
};