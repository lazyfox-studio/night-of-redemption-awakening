#include "../Headers/Enemy.h"
#include <math.h>

void Enemy::move()
{

    float r = sqrt((focus->x - x) * (focus->x - x) + (focus->y - y) * (focus->y - y)); //Расстояние до цели
    if (r > 1)
    {
        float c = speed / r; //Коэфицент подобия
        x += (focus->x - x) * c;
        y += (focus->y - y) * c;
    }

}