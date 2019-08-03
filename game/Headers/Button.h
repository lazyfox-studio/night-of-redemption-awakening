#pragma once
#include <SFML/Graphics.hpp>

namespace Button
{
	enum state
	{
		def,      // default
		clicked,
		hovered,
		disabled
	};

	enum action_type
	{
		no,
		void_void,
		void_arg,
		void_ref,
		void_ptr,
		void_this
	};

	struct type
	{
		sf::Texture* texture[4] = { 0 };
		bool state_exists[4] = { 0 };
		int width = 0;
		type(int);
		type(int, const char* def, const char* clicked = "", const char* hovered = "", const char* disabled = "");
		void assign_texture(state, const char*);
		void assign_texture(const char* def, const char* clicked = "", const char* hovered = "", const char* disabled = "");
	};

	class btn
	{
	protected:
		float x;
		float y;
		int width;
		int height;
		state btn_state;
		type* prototype;
		sf::Sprite sprite;
		void (*a_void_void)();
		void (*a_void_ptr)(void*);
		action_type atype;
		void* a_subject;

	public:
		bool visible;
		btn();
		btn(type*);
		virtual ~btn();

		state get_state();
		int get_width()
		{
			return width;
		}
		int get_height()
		{
			return height;
		}
		state check_state(float mouse_x, float mouse_y, bool mouse_click, bool set_state = false);
        state check_state_2(float mouse_x, float mouse_y, bool mouse_click, bool set_state = false);
		virtual void set_state(state);
		virtual void set_position(float, float) = 0;
		virtual void draw_in(sf::RenderWindow&) = 0;

		void onclick(void(*func)());
		void onclick(void(*func)(void*), void*);
		void click();
	};

	class text : public btn
	{
		char* str;              // нужно будет сделать еще и для wchar_t
		sf::Font* btn_font;
		sf::Text btn_text;
		sf::FloatRect bounds;   // границы текстового спрайта
	public:
		text();
		text(type*);
		text(type*, const char*);
		~text();

		void set_text(const char*);
		void set_color(sf::Color);
		void set_size(unsigned);
		void assign_font(sf::Font*);
		void set_state(state);
		void set_position(float, float);
		void set_width(int);
		void draw_in(sf::RenderWindow&);
	};

	class icon : public btn
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