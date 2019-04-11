#include "definitions.h"
#include "includes.h"

extern Monolith monolith;

int main()
{
	// служебные
	calculate_coefficients(c_coefficients, screen);
    window.setFramerateLimit(60);

	view.reset(sf::FloatRect(0.f, 0.f, 1280.f, 720.f));
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

	List<Unit> units;
	List<Enemy> enemies;
    List<Ally> allies;

	Player* player = new Player;
	units.add(player);
    units.add(&monolith);
    allies.add(player);
    allies.add(&monolith);

	int units_num = 2, enemies_num = 0, allies_num = 2;

	EnemyType* enemy_types[1];
	enemy_types[0] = new EnemyType(500, 0.5f, 5);
	enemy_types[0]->assign_texture("Textures/enemy1.png");

	/*
	Enemy* en2 = new Enemy(enemy1);
	units.add(en2);
	enemies.add(en2);
	en2->move_to(200, 900);
	enemies_num++;
	*/

	std::thread thr(enemies_generator, player, enemy_types[0], &units, &units_num, &enemies, &enemies_num);
	thr.detach();

	sf::Font font;
	font.loadFromFile("Fonts/handelgothictl-regular.ttf");

	sf::Text ammo_ind_pre;
	ammo_ind_pre.setFont(font);
	ammo_ind_pre.setString("Ammo: ");
	ammo_ind_pre.setCharacterSize(24);
	ammo_ind_pre.setFillColor(sf::Color::Blue);

	sf::Text ammo_ind;
	ammo_ind.setFont(font);
	ammo_ind.setCharacterSize(24);
	ammo_ind.setFillColor(sf::Color::Blue);
	int ammo_ind_num = 30;
	const char* ammo_ind_text = stringify(ammo_ind_num);

	sf::Text enemies_ind_pre;
	enemies_ind_pre.setFont(font);
	enemies_ind_pre.setString("Enemies: ");
	enemies_ind_pre.setCharacterSize(24);
	enemies_ind_pre.setFillColor(sf::Color::Blue);

	sf::Text enemies_ind;
	enemies_ind.setFont(font);
	enemies_ind.setCharacterSize(24);
	enemies_ind.setFillColor(sf::Color::Blue);
	int enemies_ind_num = enemies_num;
	const char* enemies_ind_text = stringify(enemies_ind_num);

	sf::Texture border;
	border.loadFromFile("Textures/interface/border_top.png");
	sf::Sprite border1, border2;
	border1.setOrigin(0.f, 0.f);
	border2.setOrigin(0.f, 64.f);
	border1.setTexture(border);
	border2.setTexture(border);

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
                case sf::Keyboard::Key::R:
                    Kb.R = flag;
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
				if (flag)
					Mouse.flood_control++;
			}
		}

		Mouse.x = (float)(sf::Mouse::getPosition(window).x);
		Mouse.y = (float)(sf::Mouse::getPosition(window).y);

		check_range_enemies(enemies);
        check_focus_enemies(enemies, allies);

        move_enemies(enemies, units);
        cooldown_update(units);
		control_player(player, enemies);
		int killed = kill_dead_enemies(units); // после control_player, это важно!
		units_num -= killed;
		enemies_num -= killed;

		if (player->get_ammo() != ammo_ind_num)
		{
			delete[] ammo_ind_text;
			ammo_ind_num = player->get_ammo();
			ammo_ind_text = stringify(ammo_ind_num);
			ammo_ind.setString(ammo_ind_text);
		}
		if (enemies_num != enemies_ind_num)
		{
			delete[] enemies_ind_text;
			enemies_ind_num = enemies_num;
			enemies_ind_text = stringify(enemies_ind_num);
			enemies_ind.setString(enemies_ind_text);
		}

		float ammo_ind_pos_x = player->getX() - screen.w / 2 + 5.0f, ammo_ind_pos_y = player->getY() - screen.h / 2 + 35.0f;
		ammo_ind_pre.setPosition(sf::Vector2f(ammo_ind_pos_x, ammo_ind_pos_y));
		ammo_ind.setPosition(sf::Vector2f(ammo_ind_pos_x + 80.f, ammo_ind_pos_y));
		enemies_ind_pre.setPosition(sf::Vector2f(ammo_ind_pos_x - 1.5f, ammo_ind_pos_y + 25.f));
		enemies_ind.setPosition(sf::Vector2f(ammo_ind_pos_x + 110.f, ammo_ind_pos_y + 25.f));

		float border_pos_x = player->getX() - screen.w / 2, border_pos_y = player->getY() - screen.h / 2 - 48.f;
		border1.setPosition(border_pos_x, border_pos_y);
		border2.setPosition(border_pos_x, border_pos_y + screen.h + 48.f);

		window.clear();
        window.setView(view);
		window.draw(background);
		draw_all(units);

		window.draw(ammo_ind_pre);
		window.draw(ammo_ind);
		window.draw(enemies_ind_pre);
		window.draw(enemies_ind);

		window.draw(border1);
		window.draw(border2);

		window.display();
	}

	return 0;
}