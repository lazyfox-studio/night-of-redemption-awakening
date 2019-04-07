#include "definitions.h"
#include "includes.h"

extern Monolith monolith;

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

	List<Unit> units;
	List<Enemy> enemies;
    List<Ally> allies;

	Player* player = new Player;
	units.add(player);
    units.add(&monolith);
    allies.add(player);
    allies.add(&monolith);

	EnemyType* enemy1 = new EnemyType(100, 0.5f, 5);
	enemy1->assign_texture("Textures/enemy1.png");

	Enemy* en = new Enemy(enemy1);
	units.add(en);
	enemies.add(en);
	en->move_to(200, 200);

	Enemy* en2 = new Enemy(enemy1);
	units.add(en2);
	enemies.add(en2);
	en->move_to(200, 900);

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
			}
			if ((event.type == sf::Event::MouseButtonPressed) || (event.type == sf::Event::MouseButtonReleased))
			{
				bool flag = (event.type == sf::Event::MouseButtonPressed);
				switch (event.key.code)
				{
				case sf::Mouse::Button::Left:
					Mouse.Left = flag;
					break;
				case sf::Mouse::Button::Right:
					Mouse.Right = flag;
					break;
				case sf::Mouse::Button::Middle:
					Mouse.Middle = flag;
					break;
				}
			}
		}

        range_check_enemies(enemies);
        check_focus_enemies(enemies, allies);
        move_enemies(enemies);
		move_player(player, enemies);
        kill_enemies(enemies);

		window.clear();
        window.setView(view);
		window.draw(background);
		draw_all(units);
		window.display();
	}

	return 0;
}