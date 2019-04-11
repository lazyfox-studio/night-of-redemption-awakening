#include "../../Headers/Allies/Player.h"
#include <iostream>

Player::Player() : Ally((float)screen.w / 2.0f, (float)screen.h / 2.0f, max_health, 4.0f, 0), damage(80)
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
    float angle = 3.1415f * (360.f + pov) / 180.f;
    for (ListItem<Enemy>* i = enemies.head; i; i = i->next)
    {
        if (i->value->r < range) {
            _x = i->value->x;
            _y = i->value->y;
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

void Player::move(float dbx, float dby, List<Unit>& units, bool is_shift)
{
    bool x_unlock = true, y_unlock = true;
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

    for (ListItem<Unit>* i = units.head; i; i = i->next)
    {
        bool x_left = false, x_right = false, y_left = false, y_right = false, x_space = false, y_space = false;
        if (i->value != this) {
            //Всевозможные варианты пересечения
            if ((x + dx + UNIT_SIZE > i->value->getX()) && (x + UNIT_SIZE < i->value->getX())) x_left = true;
            if ((x + dx - UNIT_SIZE < i->value->getX()) && (x - UNIT_SIZE > i->value->getX())) x_right = true;
            if ((y + dy + UNIT_SIZE > i->value->getY()) && (y + UNIT_SIZE < i->value->getY())) y_left = true;
            if ((y + dy - UNIT_SIZE < i->value->getY()) && (y - UNIT_SIZE > i->value->getY())) y_right = true;
            if ((x < i->value->getX() + UNIT_SIZE / 2) && (x > i->value->getX() - UNIT_SIZE / 2)) x_space = true;
            if ((y < i->value->getY() + UNIT_SIZE / 2) && (y > i->value->getY() - UNIT_SIZE / 2)) y_space = true;
            //Проверка на входы
            if ((x_left || x_right) && y_space)
            {
                x_unlock = false;
            }
            if ((y_left || y_right) && x_space) {
                y_unlock = false;
            }
            if ((x_left || x_right) && (y_right || y_left))
            {
                x_unlock = false;
                y_unlock = false;
            }
        }
    }

	if (is_edge_of_terrain(dx, dy))
		return;
    if (x_unlock)
    {
        x += dx;
        view.move(dx, 0);
        sprite.move(dx, 0);
    }
    if (y_unlock)
    {
        y += dy;
        view.move(0, dy);
        sprite.move(0, dy);
    }
}

int Player::get_ammo()
{
	return ammo;
}

int Player::get_stamina()
{
	return stamina;
}
