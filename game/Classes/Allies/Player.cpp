#include "../../Headers/Allies/Player.h"
#include <iostream>

Player::Player() : 
	Ally((float)map.w / 2.0f, (float)map.h / 2.0f, max_health, 4.0f, 0), damage(80)
{
	sprite.assign_texture("Textures/player.png", 5, SPRITE_SIZE, SPRITE_SIZE);
	sprite.set_origin(SPRITE_SIZE / 2.0f, SPRITE_SIZE / 2.0f);
	sprite.set_position(x, y);
    ammo = AK74_MAGASINE;
    stamina = MAX_STAMINA;
    player_sound.shoot.loadFromFile("Sounds/Player/shoot.wav");
    player_sound.reload.loadFromFile("Sounds/Player/reload.wav");
	move_flood_control[0] = move_flood_control[1] = 0;
	score = 0;
}

Player::~Player()
{
    
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
			increase_score(100);
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
    if ((stamina > 0) && (is_shift) && (dbx || dby))
    {
        shift = 1.f;
        stamina--;
    }
    else
    {
        shift = 0.f;
        if (stamina < MAX_STAMINA) 
			stamina++;
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
        bool x_left, x_right, y_left, y_right, x_space, y_space;
        if (i->value != this)
		{
            // Всевозможные варианты пересечения
			float _x = i->value->getX(), _y = i->value->getY();
			x_left  = ((x + dx + UNIT_SIZE > _x) && (x + dx < _x));
			x_right = ((x + dx - UNIT_SIZE < _x) && (x + dx > _x));
			y_left  = ((y + dy + UNIT_SIZE > _y) && (y + dy < _y));
			y_right = ((y + dy - UNIT_SIZE < _y) && (y + dy > _y));
			x_space = ((x < _x + UNIT_SIZE / 2)  && (x > _x - UNIT_SIZE / 2));
			y_space = ((y < _y + UNIT_SIZE / 2)  && (y > _y - UNIT_SIZE / 2));
            // Проверка на входы
			x_unlock &= !((x_left || x_right) && y_space);
			y_unlock &= !((y_left || y_right) && x_space);
			x_unlock &= !((x_left || x_right) && (y_right || y_left));
			y_unlock &= !((x_left || x_right) && (y_right || y_left));
        }
    }

	if ((x + dx < map.padding_x) || (x + dx > map.w - map.padding_x) || !x_unlock)
	{
		dx = 0;
	}
	if ((y + dy < map.padding_y) || (y + dy > map.h - map.padding_y) || !y_unlock)
	{
		dy = 0;
	}
	{
		x += dx;
		y += dy;
		view.move(dx, dy);
		sprite.move(dx, dy);
		move_flood_control[0]++;
		if (move_flood_control[0] - move_flood_control[1] > 5)
		{
			move_flood_control[1] = move_flood_control[0];
			sprite.next_frame();
		}
	}
}

void Player::increase_score(int delta)
{
	score += delta;
}

int Player::get_ammo()
{
	return ammo;
}

int Player::get_stamina()
{
	return stamina;
}

int Player::get_score()
{
	return score;
}

void Player::health_regen()
{
	sf::Clock clock;
	do
	{
		if (clock.getElapsedTime().asMilliseconds() >= 2000)
		{
			clock.restart();
			if ((health > 0) && (health < max_health))
				health += 1;
		}
	} while (1);
}
