#pragma once
#include <SFML/Graphics.hpp>

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