#pragma once
#include <SFML/Graphics.hpp>

namespace Button
{
	enum state
	{
		def,      // default
		hovered,
		clicked,
		disabled
	};

	struct type
	{
		sf::Texture* texture[4] = { 0 };
		bool state_exists[4] = { 0 };
		int width = 0;
		type(int);
		void assign_texture(state, const char*);
	};

	class btn
	{
	protected:
		int x;
		int y;
		int width;
		int height;
		state btn_state;
		type* prototype;
		sf::Sprite sprite;
		void (*action)();

	public:
		btn();
		btn(type*);
		virtual ~btn();

		state get_state();
		state check_state(float mouse_x, float mouse_y, bool mouse_click);
		virtual void set_state(state) = 0;
		virtual void set_position(float, float) = 0;
		virtual void draw_in(sf::RenderWindow&) = 0;

		void onclick(void(*func)());
		void click();
	};

	class text : btn
	{
		char* str;
		sf::Font* btn_font;
		sf::Text btn_text;
		sf::FloatRect bounds;
	public:
		text();
		text(type*);
		text(type*, const char*);
		~text();

		void set_text(const char*);
		void set_color(sf::Color);
		void assign_font(sf::Font*);
		void set_state(state);
		void set_position(float, float);
		void draw_in(sf::RenderWindow&);
	};

	class icon : btn
	{
		sf::Texture* icon_texture;
		sf::Sprite icon_sprite;
	public:
		icon();
		icon(type*);
		~icon();

		void assign_icon(const char*);
		void set_state(state);
		void set_position(float, float);
		void draw_in(sf::RenderWindow&);
	};
}