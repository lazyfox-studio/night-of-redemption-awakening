#pragma once
#include <SFML/Graphics.hpp>

struct EnemyType
{
	int health = 0;
	float speed = 0;
	int damage = 0;
	sf::Texture* texture = new sf::Texture;
	sf::Texture* texture_attack = new sf::Texture;

	EnemyType(int _health, float _speed, int _damage) :
		health(_health), speed(_speed), damage(_damage) {}

	void assign_texture(const char* t)
	{
		texture->loadFromFile(t);
	}
	void assign_texture_attack(const char* t)
	{
		texture_attack->loadFromFile(t);
	}
};