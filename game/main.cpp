#include "definitions.h"
#include "includes.h"


int main()
{
	view.reset(sf::FloatRect(0.f, 0.f, 2560.f, 1440.f));
	sf::RectangleShape background(sf::Vector2f(2560.f, 1440.f));
	sf::Texture bgtexture;
	bgtexture.loadFromFile("Textures/map.png");
	//background.setT;
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(shape);
		window.display();
	}

	return 0;
}