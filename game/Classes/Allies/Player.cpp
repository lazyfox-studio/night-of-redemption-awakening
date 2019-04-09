#include "../../Headers/Allies/Player.h"
#include <iostream>

Player::Player() : Ally((float)screen.w / 2.0f, (float)screen.h / 2.0f, 200, 2.0f, 0), damage(80)
{
    texture->loadFromFile("Textures/player.png");
    texture->setSmooth(true);
    sprite.setTexture(*texture);
    sprite.setTextureRect(sf::IntRect(0, 0, SPRITE_SIZE, SPRITE_SIZE));
    sprite.setOrigin(sf::Vector2f(SPRITE_SIZE / 2.0f, SPRITE_SIZE / 2.0f));
    sprite.setPosition(x, y);
    ammo = AK74_MAGASINE;
}

Player::~Player()
{
    delete texture;
}

void Player::shoot(List<Enemy> & enemies) {
    if ((damage_cooldown > 0) || (ammo < 1))
    {
        return;
    }
    Enemy* target = nullptr;
    float range = float(INT_MAX);
    float _x, _y;
    float angle = 3.14f * (360.f + pov) / 180.f;
    std::cout << pov << std::endl;
    for (ListItem<Enemy>* i = enemies.head; i; i = i->next)
    {
        if (i->value->r < range) {
            _x = i->value->x;
            _y = i->value->y;
            float _sin = sin(angle), _cos = cos(angle);
            if ((pov < 90) && (pov > -90))
            {
                if (
                    (-1 * (((_x - UNIT_SIZE / 2) - x) * _sin - ((_y + UNIT_SIZE / 2) - y) * _cos) >= 0)
                    &&
                    (-1 * (((_x + UNIT_SIZE / 2) - x) * _sin - ((_y - UNIT_SIZE / 2) - y) * _cos) <= 0)
                    &&
                    (_x > x)
                    )
                {
                    target = i->value;
                    range = target->r;
                }
            }
            else if ((pov > 90) || (pov < -90))
            {
                if (
                    (((_x - UNIT_SIZE / 2) - x) * _sin - ((_y + UNIT_SIZE / 2) - y) * _cos >= 0)
                    &&
                    (((_x + UNIT_SIZE / 2) - x) * _sin - ((_y - UNIT_SIZE / 2) - y) * _cos <= 0)
                    &&
                    (_x < x)
                    )
                {
                    target = i->value;
                    range = target->r;
                }
            }
            else if (pov == 90)
            {
                if (_y > y)
                {
                    if (((_x - UNIT_SIZE / 2) < x) && ((_x + UNIT_SIZE / 2) > x))
                    {
                        target = i->value;
                        range = target->r;
                    }
                }
            }
            else if ((pov == -90) || (pov == -270))
            {
                if (_y < y)
                {
                    if (((_x - UNIT_SIZE / 2) < x) && ((_x + UNIT_SIZE / 2) > x))
                    {
                        target = i->value;
                        range = target->r;
                    }
                }
            }
        }
    }
    if (target != nullptr)
    {
		target->health -= damage;
		if (target->health <= 0)
		{
			target->death();
			enemies.drop(target);
		}
    }
    ammo--;
    damage_cooldown = AK74_ATTAK_SPEED;
}

void Player::reload()
{
    ammo = AK74_MAGASINE;
    damage_cooldown = AK74_RELOAD_TIME;
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

int Player::get_ammo()
{
	return ammo;
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
