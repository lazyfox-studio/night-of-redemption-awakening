#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#define COUNT_OF_TRACKS 5
#define TRACK_END_CHECK_COOLDOWN 120

struct soundtrack
{
	sf::Music track[5];
	int current_track;
	int cooldown;

	soundtrack()
	{
		current_track = 4;
		cooldown = TRACK_END_CHECK_COOLDOWN;
		track[0].openFromFile("Music/Cephalopod.ogg");
		track[1].openFromFile("Music/Exit the Premises.ogg");
		track[2].openFromFile("Music/In a Heartbeat.ogg");
		track[3].openFromFile("Music/Rocket.ogg");
		track[4].openFromFile("Music/Shiny Tech.ogg");
		track[current_track].play();
	}

	void control()
	{
		if (cooldown > 0)
		{
			cooldown--;
			return;
		}
		if ((track[current_track].getPlayingOffset() == sf::Time()) && (cooldown == 0))
		{
			if (current_track < COUNT_OF_TRACKS - 1)
			{
				current_track++;
			}
			else
			{
				current_track = 0;
			}
			cooldown = TRACK_END_CHECK_COOLDOWN;
			track[current_track].play();
			std::cout << current_track;
		}
	}
};