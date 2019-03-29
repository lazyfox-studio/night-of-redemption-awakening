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
		std::cout << "Cant open";
	};
	background.setTexture(bgtexture);
	background.setPosition(sf::Vector2f(0, 0));
	float vc_x = 1280.f / 2.f, vc_y = 720.f / 2.f;

	view.setCenter(vc_x, vc_y);
	view.zoom(0.5f);

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
			if (event.type == sf::Event::KeyPressed)
			{
				switch (event.key.code)
				{
				case sf::Keyboard::Key::Right:
					if(view.getCenter().x < 1280)
						view.move(10, 0);
					break;
				case sf::Keyboard::Key::Left:
					if (view.getCenter().x > 640)
						view.move(-10, 0);
					break;
				case sf::Keyboard::Key::Up:
					if (view.getCenter().y > 360)
						view.move(0, -10);
					break;
				case sf::Keyboard::Key::Down:
					if (view.getCenter().y < 720)
						view.move(0, 10);
					break;
				}
				window.setView(view);
			}
		}

		window.clear();

		window.draw(background);
		//window.draw(shape);

		window.display();
	}

	return 0;
}