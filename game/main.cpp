#include "definitions.h"
#include "includes.h"

int main()
{
	// служебные
	calculate_coefficients(c_coefficients, screen);

	view.reset(sf::FloatRect(0.f, 0.f, 2560.f, 1440.f));
	sf::Sprite background;
	sf::Texture bgtexture;
	if (!bgtexture.loadFromFile("Textures/map.png"))
	{
		std::cout << "Cant open";
	};
	background.setTexture(bgtexture);
	background.setPosition(sf::Vector2f(0, 0));
	float vc_x = (float)screen.w / 2.f, vc_y = (float)screen.h / 2.f;

	view.setCenter(vc_x, vc_y);
	view.zoom(0.5f);

	Person* player = new Person;

	Unit* units[1];
	units[0] = player;

	List<Unit> Lunits;
	Lunits.add(player);

	window.setView(view);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
            if (event.type == sf::Event::Closed)
                window.close();
			if ((event.type == sf::Event::KeyPressed) || (event.type == sf::Event::KeyReleased))
			{
				bool flag = (event.type == sf::Event::KeyPressed);
				switch (event.key.code)
				{
				case sf::Keyboard::Key::W:
					Kb.W = flag;
					break;
				case sf::Keyboard::Key::A:
					Kb.A = flag;
					break;
				case sf::Keyboard::Key::S:
					Kb.S = flag;
					break;
				case sf::Keyboard::Key::D:
					Kb.D = flag;
					break;
				case sf::Keyboard::Key::Q:
					Kb.Q = flag;
					break;
				case sf::Keyboard::Key::E:
					Kb.E = flag;
					break;
				case sf::Keyboard::Key::LShift:
					Kb.LShift = flag;
					break;
				}
				//window.setView(view);
			}
		}

		move_all(player);
		window.clear();
        window.setView(view);
		window.draw(background);
		draw_all(units, 1);
		window.display();
	}

	return 0;
}