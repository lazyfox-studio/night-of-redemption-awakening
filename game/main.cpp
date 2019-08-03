#include "definitions.h"
#include "includes.h"

extern Monolith monolith;
extern soundtrack music;

int main()
{
	font.loadFromFile("Fonts/handelgothictl-regular.ttf");
	Init::choose_resolution();

	window.create(sf::VideoMode(Screen::w, Screen::h), "Night of Redemption: Awakening", sf::Style::Fullscreen);
    window.setFramerateLimit(60);
	view.reset(sf::FloatRect(0.f, 0.f, Screen::w, Screen::h));

	// Main map
	sf::Sprite background;
	sf::Texture bgtexture;
	bgtexture.loadFromFile("Textures/map.png");
	background.setTexture(bgtexture);
	background.setPosition(sf::Vector2f(0, 0));

	float vc_x = (float)Screen::w / 2.f, vc_y = (float)Screen::h / 2.f;
	

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

	std::thread thr(enemies_generator, player, enemy_types[0], &units, &units_num, &enemies, &enemies_num);
	thr.detach();
	/*std::thread regen(&(Player::health_regen), player);
	regen.detach();*/

	// Ammo pre-text
	sf::Text ammo_ind_pre;
	ammo_ind_pre.setFont(font);
	ammo_ind_pre.setString("Ammo: ");
	ammo_ind_pre.setCharacterSize(24);
	ammo_ind_pre.setFillColor(sf::Color::White);

	//Game over text
	sf::Text over_text;
	over_text.setFont(font);
	over_text.setString("GAME OVER!");
	over_text.setCharacterSize(72);
	over_text.setFillColor(sf::Color::White);

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

	//Menu
	sf::Text menu_title, menu_info1, menu_info2;
	menu_title.setFont(font);
	menu_title.setString("NIGHT OF REDEMPTION");
	menu_title.setCharacterSize(27);
	
	menu_title.setFillColor(sf::Color::Yellow);

	menu_info1.setOutlineThickness(0.f);
	menu_info1.setFont(font);
	menu_info1.setString("By Mikhail Zoreev & Maksim Vlasov");
	menu_info1.setCharacterSize(16);
	menu_info1.setFillColor(sf::Color::Red);

	menu_info2.setFont(font);
	menu_info2.setString("github.com/unn-ss/night-of-redemption-awakening");
	menu_info2.setCharacterSize(11);
	menu_info2.setFillColor(sf::Color::Red);

	//Menu buttons
	register Button::text pause_buttons[3];
	for (int i = 0; i < 3; i++)
	{
		pause_buttons[i] = Button::text(btn_text);
		pause_buttons[i].set_color(sf::Color::White);
		pause_buttons[i].set_size(27);
		pause_buttons[i].assign_font(&font);
		pause_buttons[i].set_text("Play");
		pause_buttons[i].set_width(340);
	}
	pause_buttons[0].set_text("Play");
	pause_buttons[0].onclick(resume_game, pause_btn);
	pause_buttons[1].set_text(is_music ? "Music: On" : "Music: Off");
	pause_buttons[1].onclick(is_music ? pause_music : play_music, pause_buttons + 1);
	pause_buttons[2].set_text("Quit");
	pause_buttons[2].onclick(stop_game);

	buttons.add(pause_buttons);
	buttons.add(pause_buttons + 1);
	buttons.add(pause_buttons + 2);

	//

	sf::RectangleShape dark_pause(sf::Vector2f(Screen::w, Screen::h));
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
					Keyboard::W = flag;
					break;
				case sf::Keyboard::Key::A:
					Keyboard::A = flag;
					break;
				case sf::Keyboard::Key::S:
					Keyboard::S = flag;
					break;
				case sf::Keyboard::Key::D:
					Keyboard::D = flag;
					break;
				case sf::Keyboard::Key::Q:
					Keyboard::Q = flag;
					break;
				case sf::Keyboard::Key::E:
					Keyboard::E = flag;
					break;
                case sf::Keyboard::Key::R:
                    Keyboard::R = flag;
                    break;
				case sf::Keyboard::Key::LShift:
					Keyboard::LShift = flag;
					break;
				case sf::Keyboard::Key::Escape:
					Keyboard::Escape = flag;
					break;
				}
			}
			if ((event.type == sf::Event::MouseButtonPressed) || (event.type == sf::Event::MouseButtonReleased))
			{
				bool flag = (event.type == sf::Event::MouseButtonPressed);
				switch (event.key.code)
				{
				case sf::Mouse::Button::Left:
					Mouse::Left = flag;
                    check_buttons(buttons);
					break;
				case sf::Mouse::Button::Right:
					Mouse::Right = flag;
					break;
				case sf::Mouse::Button::Middle:
					Mouse::Middle = flag;
					break;
				}
				if (flag)
					Mouse::flood_control[0]++;
			}
		}
			Mouse::x = (float)(sf::Mouse::getPosition(window).x);
			Mouse::y = (float)(sf::Mouse::getPosition(window).y);

            check_buttons_2(buttons);

		if (!is_paused && !is_game_over)
		{
			check_range_enemies(enemies);
			check_focus_enemies(enemies, allies);
			pause_buttons[0].visible = false;
			pause_buttons[1].visible = false;
			pause_buttons[2].visible = false;

			move_enemies(enemies, units);
			attack_enemies(enemies);
			cooldown_update(units);
			control_player(player, enemies, units);
			game_over_check(allies);
			int killed = kill_dead_enemies(units); // после control_player, это важно!
			units_num -= killed;
			enemies_num -= killed;
		}

		Corners::calculate(player);

		camoffset.x = player->getX() - vc_x;
		camoffset.y = player->getY() - vc_y;

		pause_btn->set_position(Corners::bottom_right.x - 175.f, Corners::bottom_right.y - 58.f);

		if (player->get_ammo() != ammo_ind_num)
		{
			delete[] ammo_ind_text;
			ammo_ind_num = player->get_ammo();
			ammo_ind_text = stringify(ammo_ind_num);
			if (ammo_ind_num <= 0)
			{
				ammo_ind.setFillColor(sf::Color::Red);
				ammo_ind_pre.setFillColor(sf::Color::Red);
			}
			else
			{
				ammo_ind.setFillColor(sf::Color::White);
				ammo_ind_pre.setFillColor(sf::Color::White);
			}
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


		float ammo_ind_pos_x = Corners::top_left.x + 10.0f, ammo_ind_pos_y = Corners::top_left.y + 20.0f;
		ammo_ind_pre.setPosition(sf::Vector2f(ammo_ind_pos_x, ammo_ind_pos_y));
		ammo_ind.setPosition(sf::Vector2f(ammo_ind_pos_x + 110.f, ammo_ind_pos_y));
		enemies_ind_pre.setPosition(sf::Vector2f(ammo_ind_pos_x - 1.5f, ammo_ind_pos_y + 25.f));
		enemies_ind.setPosition(sf::Vector2f(ammo_ind_pos_x + 110.f, ammo_ind_pos_y + 25.f));
		score_ind_pre.setPosition(sf::Vector2f(ammo_ind_pos_x - 1.5f, ammo_ind_pos_y + 50.f));
		score_ind.setPosition(sf::Vector2f(ammo_ind_pos_x + 110.f, ammo_ind_pos_y + 50.f));
		over_text.setPosition(sf::Vector2f(player->getX() - 250.f, player->getY() - 38));


		float border_pos_x = Corners::top_left.x, border_pos_y = Corners::top_left.y - 48.f;
		border1.setPosition(border_pos_x, border_pos_y);
		border2.setPosition(border_pos_x, Corners::bottom_left.y);

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
		
		if (is_game_over)
		{
			window.draw(over_text);
		}

		if (is_paused)
		{
			if (Mouse::Left && (Mouse::flood_control[0] - Mouse::flood_control[1] >= 1))
				Mouse::flood_control[1] = Mouse::flood_control[0];
			else
				Mouse::Left = false;
			dark_pause.setPosition(Corners::top_left.x, Corners::top_left.y);
			window.draw(dark_pause);
			menu_title.setPosition(player->getX() - menu_title.getGlobalBounds().width / 2, player->getY() - 200);
			menu_info1.setPosition(player->getX() - menu_title.getGlobalBounds().width / 2, player->getY() - 173);
			menu_info2.setPosition(player->getX() - menu_title.getGlobalBounds().width / 2, player->getY() - 156);
			pause_buttons[0].set_position(player->getX() - pause_buttons[0].get_width() / 2, player->getY() - 145);
			pause_buttons[1].set_position(player->getX() - pause_buttons[0].get_width() / 2, player->getY() - 145 + pause_buttons[0].get_height());
			pause_buttons[2].set_position(player->getX() - pause_buttons[0].get_width() / 2, player->getY() - 145 + 2 * pause_buttons[0].get_height());
			pause_buttons[0].visible = true;
			pause_buttons[1].visible = true;
			pause_buttons[2].visible = true;
			window.draw(menu_title);
			window.draw(menu_info1);
			window.draw(menu_info2);
		}

		window.draw(border1);
		window.draw(border2);
		health_bar.set_percentage((float)player->get_health() / (float)player->max_health);
		health_bar.set_position(Corners::bottom_left.x + 20.f, Corners::bottom_left.y - 30.f);
		health_bar.draw_in(window);
		if (player->get_stamina() < MAX_STAMINA)
		{
			stamina_bar.set_percentage((float)player->get_stamina() / float(MAX_STAMINA));
			stamina_bar.set_position(Corners::bottom_left.x + 40.f, Corners::bottom_left.y - 15.f);
			stamina_bar.draw_in(window);
		}
		draw_buttons(buttons);

		window.display();
	}

	return 0;
}