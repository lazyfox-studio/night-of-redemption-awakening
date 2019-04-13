#include "../Headers/Button.h"

Button::type::type(int _width)
{
	width = _width;
}

void Button::type::assign_texture(state _state, const char* file)
{
	if (state_exists[_state])
		delete texture[_state];
	texture[_state]->loadFromFile(file);
	texture[_state]->setSmooth(true);
	state_exists[_state] = true;
}

Button::btn::btn()
{
	prototype = nullptr;
	sprite.setOrigin(0.f, 0.f);
	x = y = 0.f;
	width = height = 0;
	btn_state = state::def;
}

Button::btn::btn(type* p)
{
	prototype = p;
	sprite.setOrigin(0.f, 0.f);
	x = y = 0.f;
	width = prototype->texture[state::def]->getSize().x;
	height = prototype->texture[state::def]->getSize().y;
	btn_state = state::def;
}

Button::btn::~btn()
{

}

Button::state Button::btn::get_state()
{
	return btn_state;
}

Button::state Button::btn::check_state(float mouse_x, float mouse_y, bool mouse_click)
{
	if (btn_state == state::disabled)
		return state::disabled;
	if ((mouse_x >= x) && (mouse_x <= x + width) && (mouse_y >= y) && (mouse_y <= y + width))
	{
		if (mouse_click)
			return state::clicked;
		else
			return state::hovered;
	}
	return state::def;
}

void Button::btn::onclick(void(*func)())
{
	action = func;
}

void Button::btn::click()
{
	(*action)();
}

Button::text::text() : btn()
{
	str = nullptr;
	btn_text.setOrigin(0.f, 0.f);
	bounds = btn_text.getGlobalBounds();
}

Button::text::text(type* p) : btn(p)
{
	set_state(state::def);
	str = nullptr;
	btn_text.setOrigin(0.f, 0.f);
	bounds = btn_text.getGlobalBounds();
}

Button::text::text(type* p, const char* _str) : btn(p)
{
	set_state(state::def);
	str = nullptr;
	set_text(_str);
}

Button::text::~text()
{
	if (str)
		delete[] str;
}

void Button::text::set_text(const char* _str)
{
	if (str)
		delete[] str;
	int len = 0;
	for (; _str[len]; len++);
	str = new char[len + 1];
	for (int i = 0; i < len; len++)
		str[i] = _str[i];
	str[len] = 0;
	btn_text.setString(str);
	bounds = btn_text.getGlobalBounds();
	btn_text.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void Button::text::set_color(sf::Color color)
{
	btn_text.setFillColor(color);
}

void Button::text::assign_font(sf::Font* font)
{
	btn_font = font;
	btn_text.setFont(*btn_font);
}

void Button::text::set_state(state _state)
{
	btn_state = _state;
	if (prototype->state_exists[btn_state])
		sprite.setTexture(*(prototype->texture[btn_state]));
	else
		sprite.setTexture(*(prototype->texture[state::def]));
}

void Button::text::set_position(float _x, float _y)
{
	bounds.left = _x + (bounds.left - x);
	bounds.top = _y + (bounds.top - y);
	float shift_x = bounds.width / 2.f, shift_y = bounds.height / 2.f;
	x = _x;
	y = _y;
	sprite.setPosition(x, y);
	btn_text.setPosition(x + shift_x, y + shift_y);
}

void Button::text::draw_in(sf::RenderWindow& window)
{
	window.draw(sprite);
	window.draw(btn_text);
	// ~btn();
}

Button::icon::icon() : btn()
{
	icon_texture = new sf::Texture;
}

Button::icon::icon(type* p) : btn(p)
{
	set_state(state::def);
	icon_texture = new sf::Texture;
}

Button::icon::~icon()
{
	delete icon_texture;
	// ~btn();
}

void Button::icon::assign_icon(const char* file)
{
	icon_texture->loadFromFile(file);
	icon_texture->setSmooth(true);
	icon_sprite.setTexture(*icon_texture);
}

void Button::icon::set_state(state _state)
{
	btn_state = _state;
	if (prototype->state_exists[btn_state])
		sprite.setTexture(*(prototype->texture[btn_state]));
	else
		sprite.setTexture(*(prototype->texture[state::def]));
}

void Button::icon::set_position(float _x, float _y)
{
	x = _x;
	y = _y;
	sprite.setPosition(x, y);
	icon_sprite.setPosition(x, y);
}

void Button::icon::draw_in(sf::RenderWindow& window)
{
	window.draw(sprite);
	window.draw(icon_sprite);
}
