#pragma once
#include "Functions.h"
#include "../Headers/Enemy.h"
#include "../Headers/Allies/Player.h"
#include "List.h"
#include "Screen.h"
#include <Windows.h>

struct GeneratorConfig
{
	bool enabled;   // ������ ���������� (���/����)
	int frequency;  // ������� ������� (� ��)
	int max_num;    // ������������ ���������� ��������
	GeneratorConfig(bool _enabled, int _freq, int _max) : 
		enabled(_enabled), frequency(_freq), max_num(_max) 
	{};
};

constexpr float map_width = 2560.f;
constexpr float map_height = 1440.f;

GeneratorConfig enemies_gconfig(true, 1000, 20);
void enemies_generator(Player* player, const ScreenResolution* screen, EnemyType* etype, List<Unit>* units, int* units_num, List<Enemy>* enemies, int* enemies_num)
{
	srand((unsigned)time(0));
	while (enemies_gconfig.enabled)
	{
		while (*enemies_num < enemies_gconfig.max_num)
		{
			int zone = random(1, 4);
			float x = 0.f, y = 0.f;
			switch (zone)
			{
			case 1: // ������
				x = random(player->getX() + screen->w / 2.f, map_width);
				y = random(0.0f, map_height);
				break;
			case 2: // ������
				x = random(player->getX() - screen->w / 2.f, player->getX() + screen->w / 2.f);
				y = random(player->getY() + screen->h / 2.f, map_height);
				break;
			case 3: // �����
				x = random(0.0f, player->getX() - screen->w / 2.f);
				y = random(0.0f, map_height);
				break;
			case 4: // �������
				x = random(player->getX() - screen->w / 2.f, player->getX() + screen->w / 2.f);
				y = random(0.0f, player->getY() - screen->h / 2.f);
				break;
			}
			Enemy* en = new Enemy(etype);
			units->add(en);
			enemies->add(en);
			en->move_to(200, 200);
			(*enemies_num)++;
			(*units_num)++;
			Sleep(enemies_gconfig.frequency);
		}
		Sleep(500);
	}
}