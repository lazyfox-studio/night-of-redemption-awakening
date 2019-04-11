#pragma once
#include <math.h>
#include "Ally.h"
#include "../Headers/Allies/Monolith.h"
#include "../Structures/EnemyType.h"
#include "../Headers/OverBar.h"

class Enemy : public Unit
{
    float r;                // Расстояние до цели
    int damage;             // Наносимый урон
    Ally* focus;            // Указатель на объект за которым следует противник
	EnemyType* prototype;   // Указатель на шаблон-прототип врага
	OverBar::bar health_bar;
    friend class Player;

public:
	Enemy();
	Enemy(float, float);
	Enemy(float, float, int, float, int);
	Enemy(EnemyType*);
    ~Enemy() {}

	bool is_enemy();

    void range();
    void move(List<Unit>& units);
	void move_to(float, float);
    void attack();
    void focus_change(List<Ally>&);
    void death();
	void update_health_bar();

	void fade_in();
	void draw();
};