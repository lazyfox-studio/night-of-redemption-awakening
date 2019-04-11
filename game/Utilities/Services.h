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
	coef.c1 = (float)screen.w / (float)gcd; // 16
	coef.c2 = (float)screen.h / (float)gcd; // 9
	coef.c3 = coef.c1 / 2.0f; // 8
	coef.c4 = coef.c2 / 3.0f; // 3
	coef.c5 = (float)screen.w * 6.0f; // 7680
	coef.c6 = coef.c1 * 178.75f; // 2860
	coef.c7 = (float)screen.h * 12.0f; // 8640
	coef.c8 = (float)screen.w * coef.c4; // 3840
}

// ���������� �������
inline void control_player(Player* player, List<Enemy>& enemies, List<Unit>& units)
{
	// �����������
	float dx = 0.0f, dy = 0.0f;
	if (Kb.W)
		dy -= 1.0f;
	if (Kb.A)
		dx -= 1.0f;
	if (Kb.S)
		dy += 1.0f;
	if (Kb.D)
		dx += 1.0f;
	player->move(dx, dy, units,Kb.LShift);

	// ��������
    if (Mouse.Left)
    {
        player->shoot(enemies);
    }
    if (Kb.R)
        player->reload();

	// ��������
    int angle = (int)(180 * atan((Mouse.y - (screen.h / 2)) / (Mouse.x - (screen.w / 2))) / 3.14);
    if (Mouse.x < (screen.w / 2))
    {
        angle += 180;
    }
	player->rotate_to(angle);
}

// ��������� ���� ����������
inline void draw_all(List<Unit>& units)
{
	units.foreach(&(Unit::draw));
}

// ���������� ����� ��� ������
inline void check_focus_enemies(List<Enemy>& enemies, List<Ally>& allies)
{
	enemies.foreach(&(Enemy::focus_change), allies);
}

// ���������� ���������� �� ����� ������
inline void check_range_enemies(List<Enemy>& enemies)
{
    enemies.foreach(&(Enemy::range));
}

// ����������� ������
inline void move_enemies(List<Enemy>& enemies, List <Unit>& units)
{
    enemies.foreach(&(Enemy::move), units);
}

// �������� ������ ������
bool enemy_died(Unit* unit)
{
	return (unit->get_health() <= 0) && (unit->is_enemy());
}

// �������� ������� ������
inline int kill_dead_enemies(List<Unit>& units)
{
	return units.remove_if(enemy_died);
}

//���������� �������� ����
inline void cooldown_update(List<Unit>& units)
{
    units.foreach(&(Unit::damage_cooldown_update));
}