#pragma once
#include "Ally.h"
#include <math.h>
#include "../Headers/Allies/Monolith.h"
#include <Windows.h>

struct EnemyType 
{
	int health = 0;
	float speed = 0;
	int damage = 0;
	sf::Texture* texture = new sf::Texture;

	EnemyType(int _health, float _speed, int _damage) :
		health(_health), speed(_speed), damage(_damage) {}

	void assign_texture(const char* t)
	{
		//delete texture;
		texture->loadFromFile(t);
	}
};

class Enemy : public Unit
{
    float r; //Расстояние до цели
    int damage;
    Ally* focus; //Указатель на объект за которым следует противник
	EnemyType* prototype;
    friend class Player;

	sf::RectangleShape health_bar;
public:
	Enemy();
	Enemy(float, float);
	Enemy(float, float, int, float, int);
	Enemy(EnemyType*);
    ~Enemy() {}

	bool is_enemy();

    void range();
    void move();
	void move_to(float, float);
    void attack();
    void focus_change(List<Ally>&);
    void death();
	void update_health_bar();

	void fade_in();
	void draw();
};
