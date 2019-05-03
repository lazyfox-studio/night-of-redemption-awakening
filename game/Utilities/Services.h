#pragma once
#include "List.h"
#include "../Headers/Unit.h"
#include "../Headers/Button.h"
#include "../Structures/Screen.h"
#include "../Structures/Controls.h"
#include "Functions.h"
#include "Generator.h"

bool is_any_button_pressed = false;
bool is_paused = false;
bool is_game_over = false;
bool is_music = true;
CameraOffset camoffset;
extern sf::Font font;
extern Button::type* btn_text;

// Управление игроком
inline void control_player(Player* player, List<Enemy>& enemies, List<Unit>& units)
{
	// Перемещение
	float dx = 0.0f, dy = 0.0f;
	if (Keyboard::W)
		dy -= 1.0f;
	if (Keyboard::A)
		dx -= 1.0f;
	if (Keyboard::S)
		dy += 1.0f;
	if (Keyboard::D)
		dx += 1.0f;
	player->move(dx, dy, units, Keyboard::LShift);

	// Стрельба
    if (Mouse::Left && !is_any_button_pressed)
    {
        player->shoot(enemies);
    }
    if (Keyboard::R)
        player->reload();

	// Вращение
    int angle = (int)(180 * atan((Mouse::y - (Screen::h / 2)) / (Mouse::x - (Screen::w / 2))) / 3.14);
    if (Mouse::x < (Screen::w / 2))
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
		if (i->value->check_state(camoffset.x + Mouse::x, camoffset.y + Mouse::y, Mouse::Left, true) == Button::state::clicked)
			is_any_button_pressed |= true;
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

//Проверка на game over
void game_over_check(List<Ally>& allies)
{
	for (ListItem<Ally>* i = allies.head; i; i = i->next)
	{
		if (i->value->get_health() <= 0)
		{
			is_game_over = true;
		}
	}
}

sf::RenderWindow pause_window;
void stop_game()
{
	pause_window.close();
	window.close();
}
void resume_game(void* ptr)
{
	Button::text* btn = (Button::text*)ptr;
	is_paused = false;
	btn->visible = true;
	if (is_music)
		music.play();
}
void play_music(void*);
void pause_music(void* ptr)
{
	Button::text* btn = (Button::text*)ptr;
	btn->set_text("Music: Off");
	btn->onclick(play_music, ptr);
	is_music = false;
}
void play_music(void* ptr)
{
	Button::text* btn = (Button::text*)ptr;
	btn->set_text("Music: On");
	btn->onclick(pause_music, ptr);
	is_music = true;
}
void pause(void* ptr)
{
	Button::text* btn = (Button::text*)ptr;
		is_paused = true;
		btn->visible = false;
		if (is_music)
			music.pause();
}

namespace Init
{
	sf::RenderWindow start_window;

	void set_720p()
	{
		Screen::w = 1280;
		Screen::h = 720;
		start_window.close();
	}
	
	void set_1080p()
	{
		Screen::w = 1980;
		Screen::h = 1080;
		start_window.close();
	}

	void choose_resolution()
	{
		start_window.create(sf::VideoMode(350U, 250U), "Start", sf::Style::None);

		sf::Text title;
		title.setFont(font);
		title.setString("Choose screen mode");
		title.setCharacterSize(27);
		title.setPosition(5.f, 3.f);
		title.setFillColor(sf::Color::Yellow);

		register Button::text start_buttons[2];
		for (int i = 0; i < 2; i++)
		{
			start_buttons[i] = Button::text(btn_text);
			start_buttons[i].set_color(sf::Color::White);
			start_buttons[i].set_size(27);
			start_buttons[i].assign_font(&font);
			start_buttons[i].set_text("HD");
			start_buttons[i].set_width(340);
			start_buttons[i].set_position(5., 40.f + i * 100.f);
		}
		start_buttons[0].set_text("1280x720");
		start_buttons[0].onclick(Init::set_720p);
		start_buttons[1].set_text("1920x1080");
		start_buttons[1].onclick(Init::set_1080p);

		Mouse::Left = false;
		while (start_window.isOpen())
		{
			sf::Event event;
			while (start_window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					start_window.close();
				if ((event.type == sf::Event::MouseButtonPressed) || (event.type == sf::Event::MouseButtonReleased))
				{
					bool flag = (event.type == sf::Event::MouseButtonPressed);
					switch (event.key.code)
					{
					case sf::Mouse::Button::Left:
						Mouse::Left = flag;
						break;
					case sf::Mouse::Button::Right:
						Mouse::Right = flag;
						break;
					case sf::Mouse::Button::Middle:
						Mouse::Middle = flag;
						break;
					}
					if (flag)
						Mouse::flood_control[0]++;
				}
			}
			if (Mouse::Left && (Mouse::flood_control[0] - Mouse::flood_control[1] >= 1))
				Mouse::flood_control[1] = Mouse::flood_control[0];
			else
				Mouse::Left = false;

			start_window.clear();
			Mouse::x = (float)(sf::Mouse::getPosition(start_window).x);
			Mouse::y = (float)(sf::Mouse::getPosition(start_window).y);
			for (int i = 0; i < 2; i++)
				if (start_buttons[i].check_state(Mouse::x, Mouse::y, Mouse::Left, true) == Button::state::clicked)
					is_any_button_pressed |= true;
			start_window.draw(title);
			for (int i = 0; i < 2; i++)
				start_buttons[i].draw_in(start_window);
			start_window.display();
		}
	}
}