#pragma once
#include "List.h"
#include "../Headers/Unit.h"
#include "../Structures/Screen.h"
#include "../Structures/Controls.h"
#include "Functions.h"

struct CameraOffset
{
	float x;
	float y;
};

struct Precalculated
{
	float c1, c2, c3, c4, c5, c6, c7, c8;
};
Precalculated c_coefficients;

void calculate_coefficients(Precalculated& coef, const ScreenResolution& screen)
{
	int gcd = GCD(screen.w, screen.h);
	c_coefficients.c1 = (float)screen.w / (float)gcd; // 16
	c_coefficients.c2 = (float)screen.h / (float)gcd; // 9
	c_coefficients.c3 = c_coefficients.c1 / 2.0f; // 8
	c_coefficients.c4 = c_coefficients.c2 / 3.0f; // 3
	c_coefficients.c5 = (float)screen.w * 6.0f; // 7680
	c_coefficients.c6 = c_coefficients.c1 * 178.75f; // 2860
	c_coefficients.c7 = (float)screen.h * 12.0f; // 8640
	c_coefficients.c8 = (float)screen.w * c_coefficients.c4; // 3840
}

// Управление игроком
inline void control_player(Player* player, List<Enemy>& enemies)
{
	// Перемещение
	float dx = 0.0f, dy = 0.0f;
	if (Kb.W)
		dy -= 1.0f;
	if (Kb.A)
		dx -= 1.0f;
	if (Kb.S)
		dy += 1.0f;
	if (Kb.D)
		dx += 1.0f;
	player->move(dx, dy, Kb.LShift);

	// Стрельба
    if (Mouse.Left)
    {
        player->shoot(enemies);
    }
    if (Kb.R)
        player->reload();

	// Вращение
    int angle = (int)(180 * atan((Mouse.y - (screen.h / 2)) / (Mouse.x - (screen.w / 2))) / 3.14);
    if (Mouse.x < (screen.w / 2))
    {
        angle += 180;
    }
	player->rotate_to(angle);
}

// Отрисовка всех персонажей
inline void draw_all(List<Unit>& units)
{
	units.foreach(&(Unit::draw));
}

// Вычисление целей для врагов
inline void check_focus_enemies(List<Enemy>& enemies, List<Ally>& allies)
{
	enemies.foreach(&(Enemy::focus_change), allies);
}

// Вычисление расстояний до целей врагов
inline void check_range_enemies(List<Enemy>& enemies)
{
    enemies.foreach(&(Enemy::range));
}

// Перемещение врагов
inline void move_enemies(List<Enemy>& enemies, List <Unit>& units)
{
    enemies.foreach(&(Enemy::move), units);
}

// Проверка смерти юнитов
bool enemy_died(Unit* unit)
{
	return (unit->get_health() <= 0) && (unit->is_enemy());
}

// Удаление мертвых юнитов
inline int kill_dead_enemies(List<Unit>& units)
{
	return units.remove_if(enemy_died);
}

//Обновление кулдауна атак
inline void cooldown_update(List<Unit>& units)
{
    units.foreach(&(Unit::damage_cooldown_update));
}