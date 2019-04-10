#include "../../Headers/Allies/Player.h"
#include <iostream>

Player::Player() : Ally((float)screen.w / 2.0f, (float)screen.h / 2.0f, 200, 4.0f, 0), damage(80)
{
    texture->loadFromFile("Textures/player.png");
    texture->setSmooth(true);
    sprite.setTexture(*texture);
    sprite.setTextureRect(sf::IntRect(0, 0, SPRITE_SIZE, SPRITE_SIZE));
    sprite.setOrigin(sf::Vector2f(SPRITE_SIZE / 2.0f, SPRITE_SIZE / 2.0f));
    sprite.setPosition(x, y);
    ammo = AK74_MAGASINE;
    stamina = MAX_STAMINA;
    player_sound.shoot.loadFromFile("Sounds/Player/shoot.wav");
    player_sound.reload.loadFromFile("Sounds/Player/reload.wav");
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
    sound.setBuffer(player_sound.shoot);
    sound.play();

    Enemy* target = nullptr;
    float range = float(INT_MAX);
    float _x, _y;
    float angle = 3.14f * (360.f + pov) / 180.f;
    for (ListItem<Enemy>* i = enemies.head; i; i = i->next)
    {
        if (i->value->r < range) {
            _x = i->value->x;
            _y = i->value->y;
            float _sin = sin(angle), _cos = cos(angle);
            if ((pov < 90) && (pov > -90))
            {
                if (
                    ((_y + UNIT_SIZE) - y - tan(angle) * (_x - x) > 0)
                    &&
                    ((_y - UNIT_SIZE) - y - tan(angle) * (_x - x) - 0)
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
                    ((_y + UNIT_SIZE) - y - tan(angle) * (_x - x) > 0)
                    &&
                    ((_y - UNIT_SIZE) - y - tan(angle) * (_x - x) - 0)
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
    sound.setBuffer(player_sound.reload);
    sound.play();
    ammo = AK74_MAGASINE;
    damage_cooldown = AK74_RELOAD_TIME;
}

void Player::move(float dbx, float dby, bool is_shift)
{
    float shift = is_shift;
    if ((stamina > 0) && (is_shift))
    {
        shift = 1.f;
        stamina--;
    }
    else
    {
        shift = 0.f;
        if (stamina < MAX_STAMINA) stamina++;
    }
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
