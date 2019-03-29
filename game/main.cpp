#include "definitions.h"
#include "includes.h"
#include <iostream>


int main()
{
	view.reset(sf::FloatRect(0.f, 0.f, 2560.f, 1440.f));
	sf::Sprite background;
	sf::Texture bgtexture;
	if (!bgtexture.loadFromFile("Textures/map.png"))
	{
		std::cout << "Cant open" << std::flush;
	};
	background.setTexture(bgtexture);
	background.setPosition(sf::Vector2f(0, 0));

	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	window.setView(view);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();

		window.draw(background);
		//window.draw(shape);

		window.display();
	}

	return 0;
}