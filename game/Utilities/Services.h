#pragma once
#include "List.h"
#include "../Headers/Unit.h"
#include "../Headers/Button.h"
#include "../Structures/Screen.h"
#include "../Structures/Controls.h"
#include "Functions.h"

bool is_any_button_pressed = false;

// Управление игроком
inline void control_player(Player* player, List<Enemy>& enemies, List<Unit>& units)
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
	player->move(dx, dy, units,Kb.LShift);

	// Стрельба
    if (Mouse.Left && !is_any_button_pressed)
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

inline void check_buttons(List<Button::btn>& buttons)
{
	is_any_button_pressed = false;
	for (ListItem<Button::btn>* i = buttons.head; i; i = i->next)
		if (i->value->check_state(Mouse.x, Mouse.y, Mouse.Left, true) == Button::state::clicked)
			is_any_button_pressed |= true; // тут баги какие-то, кнопка не всегда нажимается
}

inline void draw_buttons(List<Button::btn>& buttons)
{
	for (ListItem<Button::btn>* i = buttons.head; i; i = i->next)
		if (i->value->visible)
			i->value->draw_in(window);
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
inline void attack_enemies(List<Enemy>& enemies)
{
    enemies.foreach(&(Enemy::attack));
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