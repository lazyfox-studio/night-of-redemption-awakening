#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Structures/Screen.h"
#include "Headers\Allies\Monolith.h"
#include "Structures/Soundtrack.h"

sf::RenderWindow window(sf::VideoMode(screen.w, screen.h), "Night of Redemption™: Awakening");
sf::View view;
Monolith monolith;
sf::Sound sound;
soundtrack music;