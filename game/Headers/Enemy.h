#pragma once
#include "Ally.h"

class Enemy : public Unit
{
    float r; //Расстояние до цели
    float speed;
    int damage;
    int damage_cooldown; //Ограничение на скорость атак
    Ally* focus; //Указатель на объект за которым следует противник

public:
    Enemy()
    {

    }
    ~Enemy()
    {

    }

    void range();
    void move();
    virtual void attack();
    virtual void draw() = 0;
    virtual void focus_change() = 0;
    virtual void death() = 0;
};
