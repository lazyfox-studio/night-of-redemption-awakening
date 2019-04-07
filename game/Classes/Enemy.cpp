#include "../Headers/Enemy.h"
#include <math.h>
#include "../Headers/Allies/Monolith.h"

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

Enemy::Enemy(EnemyType* p) : Unit(0, 0, p->health, p->speed, 0), damage(p->damage)
{
	texture = p->texture;
	texture->setSmooth(true);
	sprite.setTexture(*texture);
    focus = &monolith;
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
    }

}

void Enemy::move_to(float _x, float _y)
{
	setX(_x);
	setY(_y);
    sprite.setPosition(_x, _y);
}

void Enemy::attack() {
    if (damage_cooldown > 0)
    {
        damage_cooldown--;
        return;
    }

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