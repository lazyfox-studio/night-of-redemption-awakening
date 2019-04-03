﻿#pragma once
#include "Ally.h"

class Enemy : public Unit
{
    float r; //Расстояние до цели
    int damage;
    int damage_cooldown; //Ограничение на скорость атак
    Ally* focus; //Указатель на объект за которым следует противник

public:
	Enemy(float _x, float _y, int _health, float _speed, float _pov) :
		Unit(_x, _y, _health, _speed, _pov) {}

    ~Enemy()
    {
    }

    void range();
    void move();
    void attack();
    void focus_change();
    void death();
};
