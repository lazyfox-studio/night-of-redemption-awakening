#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Structures/Screen.h"
#include "Headers\Allies\Monolith.h"
#include "Structures/Soundtrack.h"
#include "Headers/Button.h"

sf::RenderWindow window;
sf::View view;
Monolith monolith;
sf::Sound sound;
sf::Font font;
soundtrack music;
Button::type* btn_text = new Button::type(300, "Textures/buttons/def.png", "Textures/buttons/clicked.png", "Textures/buttons/hovered.png");