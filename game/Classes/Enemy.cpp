#include "../Headers/Enemy.h"
#include <math.h>

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
    }

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

void focus_change()
{

}

void death()
{

}