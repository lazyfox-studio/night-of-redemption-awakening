#include "../../Headers/Allies/Player.h"
#include <iostream>

Player::Player() : Ally((float)screen.w / 2.0f, (float)screen.h / 2.0f, 200, 3.0f, 0), damage(5)
{
	texture->loadFromFile("Textures/player.png");
	texture->setSmooth(true);
	sprite.setTexture(*texture);
	sprite.setTextureRect(sf::IntRect(0, 0, SPRITE_SIZE, SPRITE_SIZE));
	sprite.setOrigin(sf::Vector2f(SPRITE_SIZE / 2.0f, SPRITE_SIZE / 2.0f));
	sprite.setPosition(x, y);
}

Player::~Player()
{
}

void Player::shoot(List<Enemy>& enemies) {
    Enemy* target = nullptr;
    float range = float(INT_MAX);
    float _x, _y;
    for (ListItem<Enemy>* i = enemies.head; i; i = i->next)
    {
        _x = i->value->x;
        _y = i->value->y;
        
        float angle = 3.14 * pov / 180;
        if (i->value->r < range)
        {
            
        }
    }
    if (target != nullptr)
    {
		//std::cout << " target found";
		target->health -= damage;
		if (target->health <= 0)
		{
			target->death();
			enemies.drop(target);
		}
    }
}

void Player::move(float dbx, float dby, bool is_shift)
{
	float shift = is_shift ? 1.f : 0.f;
	float dx = 0.0f, dy = 0.0f;
	if ((dbx != 0) && (dby != 0)) //Чтобы бег по диагонали не был быстрее чем по прямой
	{
		dx = dbx * (speed + (speed * shift)) * 0.707f;
		dy = dby * (speed + (speed * shift)) * 0.707f;
	}
	else
	{
		dx = dbx * (speed + (speed * shift));
		dy = dby * (speed + (speed * shift));
	}
	if (is_edge_of_terrain(dx, dy))
		return;
	x = x + dx;
	y = y + dy;
	view.move(dx, dy);
	sprite.move(dx, dy);
}

void Player::test_ani()
{
	std::cout << " thr";
	for (;;)
	{
		sprite.rotate(15.f);
		Sleep(400);
	}
}
