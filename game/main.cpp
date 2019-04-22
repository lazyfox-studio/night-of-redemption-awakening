#include "definitions.h"
#include "includes.h"

extern Monolith monolith;
extern soundtrack music;

int main()
{
    window.setFramerateLimit(60);
	view.reset(sf::FloatRect(0.f, 0.f, 1280.f, 720.f));

	// Main map
	sf::Sprite background;
	sf::Texture bgtexture;
	bgtexture.loadFromFile("Textures/map.png");
	background.setTexture(bgtexture);
	background.setPosition(sf::Vector2f(0, 0));

	float vc_x = (float)screen.w / 2.f, vc_y = (float)screen.h / 2.f;
	

	List<Unit> units;
	List<Enemy> enemies;
    List<Ally> allies;

	Player* player = new Player;
	units.add(player);
    units.add(&monolith);
    allies.add(player);
    allies.add(&monolith);

	view.setCenter(player->getX(), player->getY());

	int units_num = 2, enemies_num = 0, allies_num = 2;

	EnemyType* enemy_types[1];
	enemy_types[0] = new EnemyType(500, 0.5f, 5);
	enemy_types[0]->assign_texture("Textures/enemy_move.png");
	enemy_types[0]->assign_texture_attack("Textures/enemy_attack.png");

	/*
	Enemy* en2 = new Enemy(enemy1);
	units.add(en2);
	enemies.add(en2);
	en2->move_to(200, 900);
	enemies_num++;
	*/

	std::thread thr(enemies_generator, player, enemy_types[0], &units, &units_num, &enemies, &enemies_num);
	thr.detach();
	/*std::thread regen(&(Player::health_regen), player);
	regen.detach();*/
	font.loadFromFile("Fonts/handelgothictl-regular.ttf");

	// Ammo pre-text
	sf::Text ammo_ind_pre;
	ammo_ind_pre.setFont(font);
	ammo_ind_pre.setString("Ammo: ");
	ammo_ind_pre.setCharacterSize(24);
	ammo_ind_pre.setFillColor(sf::Color::White);

	// Ammo indicator
	sf::Text ammo_ind;
	ammo_ind.setFont(font);
	ammo_ind.setCharacterSize(24);
	ammo_ind.setFillColor(sf::Color::White);
	int ammo_ind_num = 30;
	const char* ammo_ind_text = stringify(ammo_ind_num);

	// Enemies pre-text
	sf::Text enemies_ind_pre;
	enemies_ind_pre.setFont(font);
	enemies_ind_pre.setString("Enemies: ");
	enemies_ind_pre.setCharacterSize(24);
	enemies_ind_pre.setFillColor(sf::Color::White);

	// Enemies counter
	sf::Text enemies_ind;
	enemies_ind.setFont(font);
	enemies_ind.setCharacterSize(24);
	enemies_ind.setFillColor(sf::Color::White);
	int enemies_ind_num = enemies_num;
	const char* enemies_ind_text = stringify(enemies_ind_num);

	// Score pre-text
	sf::Text score_ind_pre;
	score_ind_pre.setFont(font);
	score_ind_pre.setString("Score: ");
	score_ind_pre.setCharacterSize(24);
	score_ind_pre.setFillColor(sf::Color::White);

	// Score counter
	sf::Text score_ind;
	score_ind.setFont(font);
	score_ind.setCharacterSize(24);
	score_ind.setFillColor(sf::Color::White);
	int score_ind_num = 1;
	const char* score_ind_text = stringify(score_ind_num);

	// Borders
	sf::Texture border;
	border.loadFromFile("Textures/interface/border_top.png");
	sf::Sprite border1, border2;
	border1.setOrigin(0.f, 0.f);
	border2.setOrigin(0.f, 64.f);
	border1.setTexture(border);
	border2.setTexture(border);

	// Player health and stamina bars
	OverBar::bar health_bar(OverBar::color::green), stamina_bar(OverBar::color::blue);
	health_bar.set_width(200.f);
	stamina_bar.set_width(150.f);

	// Button Test
	List<Button::btn> buttons;
	register Button::text* pause_btn = new Button::text(btn_text);
	pause_btn->set_color(sf::Color::White);
	pause_btn->set_size(28);
	pause_btn->assign_font(&font);
	pause_btn->set_text("Menu");
	pause_btn->set_width(170);
	pause_btn->onclick(pause, (void*)pause_btn);
	buttons.add(pause_btn);

	sf::RectangleShape dark_pause(sf::Vector2f(float(screen.w), float(screen.h)));
	dark_pause.setFillColor(sf::Color(0, 0, 0, 200));

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
				case sf::Keyboard::Key::Escape:
					Kb.Escape = flag;
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
					Mouse.flood_control[0]++;
			}
		}

		Mouse.x = (float)(sf::Mouse::getPosition(window).x);
		Mouse.y = (float)(sf::Mouse::getPosition(window).y);

		check_buttons(buttons);

		if (!is_paused)
		{
			check_range_enemies(enemies);
			check_focus_enemies(enemies, allies);

			move_enemies(enemies, units);
			attack_enemies(enemies);
			cooldown_update(units);
			control_player(player, enemies, units);
			int killed = kill_dead_enemies(units); // после control_player, это важно!
			units_num -= killed;
			enemies_num -= killed;
		}

		corners.calculate(&screen, player);

		camoffset.x = player->getX() - vc_x;
		camoffset.y = player->getY() - vc_y;

		pause_btn->set_position(corners.bottom_right.x - 175.f, corners.bottom_right.y - 58.f);
		//resume_btn->set_position(corners.bottom_right.x - 220.f, corners.bottom_right.y - 62.f);

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
		if (player->get_score() != score_ind_num)
		{
			delete[] score_ind_text;
			score_ind_num = player->get_score();
			score_ind_text = stringify(score_ind_num);
			score_ind.setString(score_ind_text);
		}


		float ammo_ind_pos_x = corners.top_left.x + 10.0f, ammo_ind_pos_y = corners.top_left.y + 20.0f;
		ammo_ind_pre.setPosition(sf::Vector2f(ammo_ind_pos_x, ammo_ind_pos_y));
		ammo_ind.setPosition(sf::Vector2f(ammo_ind_pos_x + 110.f, ammo_ind_pos_y));
		enemies_ind_pre.setPosition(sf::Vector2f(ammo_ind_pos_x - 1.5f, ammo_ind_pos_y + 25.f));
		enemies_ind.setPosition(sf::Vector2f(ammo_ind_pos_x + 110.f, ammo_ind_pos_y + 25.f));
		score_ind_pre.setPosition(sf::Vector2f(ammo_ind_pos_x - 1.5f, ammo_ind_pos_y + 50.f));
		score_ind.setPosition(sf::Vector2f(ammo_ind_pos_x + 110.f, ammo_ind_pos_y + 50.f));

		float border_pos_x = corners.top_left.x, border_pos_y = corners.top_left.y - 48.f;
		border1.setPosition(border_pos_x, border_pos_y);
		border2.setPosition(border_pos_x, corners.bottom_left.y);

		music.control();

		window.clear();
        window.setView(view);
		window.draw(background);
		draw_all(units);

		window.draw(ammo_ind_pre);
		window.draw(ammo_ind);
		window.draw(enemies_ind_pre);
		window.draw(enemies_ind);
		window.draw(score_ind_pre);
		window.draw(score_ind);

		window.draw(border1);
		window.draw(border2);

		if (player->get_stamina() < MAX_STAMINA)
		{
			stamina_bar.set_percentage((float)player->get_stamina() / float(MAX_STAMINA));
			stamina_bar.set_position(corners.bottom_left.x + 40.f, corners.bottom_left.y - 15.f);
			stamina_bar.draw_in(window);
		}

		health_bar.set_percentage((float)player->get_health() / (float)player->max_health);
		health_bar.set_position(corners.bottom_left.x + 20.f, corners.bottom_left.y - 30.f);
		health_bar.draw_in(window);
		draw_buttons(buttons);

		if (is_paused)
		{
			dark_pause.setPosition(player->getX(), player->getY());
			window.draw(dark_pause);
		}

		window.display();
	}

	return 0;
}