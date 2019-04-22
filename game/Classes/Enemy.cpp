#include "../Headers/Enemy.h"
#include <iostream>

extern Monolith monolith;

Enemy::Enemy() : Unit() 
{
	attack_flood_control[0] = attack_flood_control[1] = attacking = 0;
}

Enemy::Enemy(float _x, float _y) : Unit(_x, _y) 
{
	attack_flood_control[0] = attack_flood_control[1] = attacking = 0;
}

Enemy::Enemy(float _x, float _y, int _health, float _speed, int _pov) :
	Unit(_x, _y, _health, _speed, _pov) 
{
	attack_flood_control[0] = attack_flood_control[1] = attacking = 0;
}

Enemy::Enemy(EnemyType* p) : Unit(0, 0, p->health, p->speed, 0), damage(p->damage), prototype(p)
{
	sprite.assign_texture(p->texture);
	sprite.set_origin(SPRITE_SIZE / 2.0f, SPRITE_SIZE / 2.0f);
	sprite.set_color(sf::Color(255, 255, 255, 0));
    focus = &monolith;
	attack_flood_control[0] = attack_flood_control[1] = attacking = 0;
	
	health_bar.set_color(OverBar::color::red);
	health_bar.set_width(UNIT_SIZE);
}

bool Enemy::is_enemy()
{
	return true;
}

void Enemy::range() {
    r = sqrt((focus->x - x) * (focus->x - x) + (focus->y - y) * (focus->y - y));
}

void Enemy::move(List<Unit>& units)
{
    if (r > UNIT_SIZE)
    {
        bool x_unlock = true, y_unlock = true;
        
        float c = speed / r;              // Коэффицент подобия
        float dx = (focus->x - x) * c;
        float dy = (focus->y - y) * c;
        for (ListItem<Unit>* i = units.head; i; i = i->next)
        {
            bool x_left = false, x_right = false, y_left = false, y_right = false, x_space = false, y_space = false;
			if (i->value != this)
			{
				// Всевозможные варианты пересечения
				float _x = i->value->getX(), _y = i->value->getY();
				x_left = ((x + dx + UNIT_SIZE > _x) && (x + dx < _x));
				x_right = ((x + dx - UNIT_SIZE < _x) && (x + dx > _x));
				y_left = ((y + dy + UNIT_SIZE > _y) && (y + dy < _y));
				y_right = ((y + dy - UNIT_SIZE < _y) && (y + dy > _y));
				x_space = ((x < _x + UNIT_SIZE / 2) && (x > _x - UNIT_SIZE / 2));
				y_space = ((y < _y + UNIT_SIZE / 2) && (y > _y - UNIT_SIZE / 2));
				// Проверка на входы
				x_unlock &= !((x_left || x_right) && y_space);
				y_unlock &= !((y_left || y_right) && x_space);
				x_unlock &= !((x_left || x_right) && (y_right || y_left));
				y_unlock &= !((x_left || x_right) && (y_right || y_left));
			}
        }
        if (x_unlock == true) 
			x += dx;
        if (y_unlock == true) 
			y += dy;
        sprite.set_position(x, y);

        int angle = (int)(180 * atan((focus->y - y) / (focus->x - x)) / 3.14);
        if (focus->x < x)
            angle += 180;
        sprite.set_rotation((float)angle);
    }
    int angle = (int)(180 * atan((focus->y - y) / (focus->x - x)) / 3.14);
    if (focus->x < x)
        angle += 180;
    sprite.set_rotation((float)angle);
}

void Enemy::move_to(float _x, float _y)
{
	setX(_x);
	setY(_y);
    sprite.set_position(_x, _y);
}

void Enemy::attack() {
	if (attacking)
	{
		attack_flood_control[0]++;
		if (attack_flood_control[0] - attack_flood_control[1] > 3)
		{
			attack_flood_control[1] = attack_flood_control[0];
			sprite.next_frame();
		}
	}
    if (r <= UNIT_SIZE * 1.414) //Радиус
    {
		if(!attacking)
			sprite.assign_texture(prototype->texture_attack, 9, 200, 200);
		attacking = true;
		if (damage_cooldown <= 0)
		{
			focus->health -= damage;
			damage_cooldown = 60; //Подобрать значение!!!
		}
    }
	else
	{
		sprite.assign_texture(prototype->texture, 1, 160, 160);
		attacking = false;
	}
	damage_cooldown--;
}

void Enemy::focus_change(List<Ally>& allies)
{
    for (ListItem<Ally>* i = allies.head; i; i = i->next)
    {
		float _x = i->value->x, _y = i->value->y;
        if (r * r > (_x - x) * (_x - x) + (_y - y) * (_y - y))
        {
            focus = i->value;
        }
    }
}

void Enemy::death()
{
    
}

void Enemy::update_health_bar()
{
	health_bar.set_percentage((float)health / (float)(prototype->health));
	health_bar.set_position(x - UNIT_SIZE / 2, y - UNIT_SIZE / 2 - 5.0f);
}

void Enemy::fade_in()
{
	int alpha = 0;
	sf::Clock clock;
	while (alpha++ < 255)
	{
		if (health < prototype->health)
		{
			sprite.set_color(sf::Color(255, 255, 255, 255));
			break;
		}
		sprite.set_color(sf::Color(255, 255, 255, alpha));
		clock.restart();
		do
		{
			if (clock.getElapsedTime().asMilliseconds() >= 1)
				break;
		} while (1);
	}
}

void Enemy::draw()
{
	update_health_bar();
	sprite.draw_in(window);
	health_bar.draw_in(window);
}