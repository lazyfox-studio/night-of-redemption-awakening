﻿#pragma once
#include "Functions.h"
#include "../Headers/Enemy.h"
#include "../Headers/Allies/Player.h"
#include "List.h"
#include "Screen.h"
#include <Windows.h>

struct GeneratorConfig
{
	bool enabled;   // Статус генератора (вкл/выкл)
	int frequency;  // Частота запуска (в мс)
	int max_num;    // Максимальное количество объектов
	GeneratorConfig(bool _enabled, int _freq, int _max) : 
		enabled(_enabled), frequency(_freq), max_num(_max) 
	{};
};

GeneratorConfig enemies_gconfig(true, 1000, 20);
void enemies_generator(Player* player, EnemyType* etype, List<Unit>* units, int* units_num, List<Enemy>* enemies, int* enemies_num)
{
	while (enemies_gconfig.enabled)
	{
		while (*enemies_num < enemies_gconfig.max_num)
		{
			srand((unsigned)time(0));
			int zone = random(1, 4);
			float x = 0.f, y = 0.f;
			switch (zone)
			{
			case 1: // правая
				x = random(player->getX() + screen.w / 2.f, map.w);
				y = random(0.0f, map.h);
				break;
			case 2: // нижняя
				x = random(player->getX() - screen.w / 2.f, player->getX() + screen.w / 2.f);
				y = random(player->getY() + screen.h / 2.f, map.h);
				break;
			case 3: // левая
				x = random(0.0f, player->getX() - screen.w / 2.f);
				y = random(0.0f, map.h);
				break;
			case 4: // верхняя
				x = random(player->getX() - screen.w / 2.f, player->getX() + screen.w / 2.f);
				y = random(0.0f, player->getY() - screen.h / 2.f);
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
