#include "../Headers/Enemy.h"

extern Monolith monolith;

Enemy::Enemy() : Unit() 
{

}

Enemy::Enemy(float _x, float _y) : Unit(_x, _y) 
{

}

Enemy::Enemy(float _x, float _y, int _health, float _speed, int _pov) :
	Unit(_x, _y, _health, _speed, _pov) 
{

}

Enemy::Enemy(EnemyType* p) : Unit(0, 0, p->health, p->speed, 0), damage(p->damage), prototype(p)
{
	texture = p->texture;
	texture->setSmooth(true);
	sprite.setTexture(*texture);
    sprite.setOrigin(sf::Vector2f(SPRITE_SIZE / 2.0f, SPRITE_SIZE / 2.0f));
	sprite.setColor(sf::Color(255, 255, 255, 0)); // for fading in
    focus = &monolith;
	
	health_bar.set_color(OverBar::color::red);
	health_bar.set_width(UNIT_SIZE);
	/*health_bar.setSize(sf::Vector2f(UNIT_SIZE, 5.0f));
	health_bar.setFillColor(sf::Color::Red);
	health_bar.setOrigin(sf::Vector2f(0.0f, 5.0f));*/
}

bool Enemy::is_enemy()
{
	return true;
}

void Enemy::range() {
    r = sqrt((focus->x - x) * (focus->x - x) + (focus->y - y) * (focus->y - y));
}

void Enemy::move()
{
    if (r > 1)
    {
        float c = speed / r; //Коэфицент подобия
        x += (focus->x - x) * c;
        y += (focus->y - y) * c;
        sprite.setPosition(x, y);
        int angle = (int)(180 * atan((focus->y - y) / (focus->x - x)) / 3.14);
        if (focus->x < x)
        {
            angle += 180;
        }
        sprite.setRotation((float)angle);
    }

}

void Enemy::move_to(float _x, float _y)
{
	setX(_x);
	setY(_y);
    sprite.setPosition(_x, _y);
}

void Enemy::attack() {
    if (damage_cooldown-- > 0)
        return;
    if (r <= 1)
    {
        //Стоило бы добавить проигрывание анимации
        focus->health -= damage;
        damage_cooldown = 5; //Подобрать значение!!!
    }
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
	while (alpha++ < 255)
	{
		if (health < prototype->health)
		{
			sprite.setColor(sf::Color(255, 255, 255, 255));
			break;
		}
		sprite.setColor(sf::Color(255, 255, 255, alpha));
		Sleep(1);
	}
}

void Enemy::draw()
{
	update_health_bar();
	window.draw(sprite);
	health_bar.draw();
}