#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Utilities/Screen.h"
#include "Headers\Allies\Monolith.h"

sf::RenderWindow window(sf::VideoMode(screen.w, screen.h), "Evil Redemption");
sf::View view;
Monolith monolith;
sf::Sound sound;