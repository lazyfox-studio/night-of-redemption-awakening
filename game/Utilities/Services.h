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
bool is_music = true;
CameraOffset camoffset;
extern sf::Font font;
extern Button::type* btn_text;

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
	player->move(dx, dy, units, Kb.LShift);

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
		if (i->value->check_state(camoffset.x + Mouse.x, camoffset.y + Mouse.y, Mouse.Left, true) == Button::state::clicked)
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

sf::RenderWindow pause_window;
void stop_game()
{
	pause_window.close();
	window.close();
}
void resume_game()
{
	pause_window.close();
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
	is_paused = true;
	Button::text* btn = (Button::text*)ptr;
	btn->visible = false;
	enemies_gconfig.max_num = 0;
	if(is_music)
		music.pause();

	pause_window.create(sf::VideoMode(350U, 400U), "Game paused", sf::Style::None);

	sf::Text title, info1, info2;
	title.setFont(font);
	title.setString("NIGHT OF REDEMPTION");
	title.setCharacterSize(27);
	title.setPosition(5.f, 3.f);
	title.setFillColor(sf::Color::Yellow);

	info1.setOutlineThickness(0.f);
	info1.setFont(font);
	info1.setString("By Mikhail Zoreev & Maksim Vlasov");
	info1.setCharacterSize(16);
	info1.setPosition(10.f, 360.f);
	info1.setFillColor(sf::Color::Red);

	info2.setFont(font);
	info2.setString("github.com/unn-ss/night-of-redemption-awakening");
	info2.setCharacterSize(11);
	info2.setPosition(10.f, 380.f);
	info2.setFillColor(sf::Color::Red);

	register Button::text pause_buttons[3];
	for (int i = 0; i < 3; i++)
	{
		pause_buttons[i] = Button::text(btn_text);
		pause_buttons[i].set_color(sf::Color::White);
		pause_buttons[i].set_size(27);
		pause_buttons[i].assign_font(&font);
		pause_buttons[i].set_text("Play");
		pause_buttons[i].set_width(340);
		pause_buttons[i].set_position(5., 40.f + i * 100.f);
	}
	pause_buttons[0].set_text("Play");
	pause_buttons[0].onclick(resume_game);
	pause_buttons[1].set_text(is_music ? "Music: On" : "Music: Off");
	pause_buttons[1].onclick(is_music ? pause_music : play_music, pause_buttons + 1);
	pause_buttons[2].set_text("Quit");
	pause_buttons[2].onclick(stop_game);

	Mouse.Left = false;
	while (pause_window.isOpen())
	{
		sf::Event event;
		while (pause_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				pause_window.close();
			if ((event.type == sf::Event::MouseButtonPressed) || (event.type == sf::Event::MouseButtonReleased))
			{
				bool flag = (event.type == sf::Event::MouseButtonPressed);
				switch (event.key.code)
				{
				case sf::Mouse::Button::Left:
					Mouse.Left = flag;
					break;
				case sf::Mouse::Button::Right:
					Mouse.Right = flag;
					break;
				case sf::Mouse::Button::Middle:
					Mouse.Middle = flag;
					break;
				}
				if (flag)
					Mouse.flood_control[0]++;
			}
		}
		if (Mouse.Left && (Mouse.flood_control[0] - Mouse.flood_control[1] >= 1))
			Mouse.flood_control[1] = Mouse.flood_control[0];
		else
			Mouse.Left = false;

		window.clear();
		Mouse.x = (float)(sf::Mouse::getPosition(pause_window).x);
		Mouse.y = (float)(sf::Mouse::getPosition(pause_window).y);
		for (int i = 0; i < 3; i++)
			if (pause_buttons[i].check_state(Mouse.x, Mouse.y, Mouse.Left, true) == Button::state::clicked)
				is_any_button_pressed |= true;
		pause_window.draw(title);
		for(int i = 0; i < 3; i++)
			pause_buttons[i].draw_in(pause_window);
		pause_window.draw(info1);
		pause_window.draw(info2);
		pause_window.display();
	}
	is_paused = false;
	enemies_gconfig.max_num = 10;
	btn->visible = true;
	if(is_music)
		music.play();
}