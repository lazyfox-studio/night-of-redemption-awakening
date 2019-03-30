#pragma once
#include <SFML/Graphics.hpp>

sf::RenderWindow window(sf::VideoMode(1280, 720), "Evil Redemption");
sf::View view;

struct ScreenResolution
{
	float x = 1280.f;
	float y = 720.f;
};

const ScreenResolution screen;