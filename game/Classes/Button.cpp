#include "../Headers/Button.h"


Button::type::type(int _width)
{
	width = _width;
}

Button::type::type(int _width, const char* def, const char* clicked, const char* hovered, const char* disabled)
{
	width = _width;
	assign_texture(def, clicked, hovered, disabled);
}

void Button::type::assign_texture(state _state, const char* file)
{
	if (state_exists[_state])
		delete texture[_state];
	if (!texture[_state])
		texture[_state] = new sf::Texture;
	texture[_state]->loadFromFile(file);
	texture[_state]->setSmooth(true);
	state_exists[_state] = true;
}

void Button::type::assign_texture(const char* def, const char* clicked, const char* hovered, const char* disabled)
{
	assign_texture(state::def, def);
	if (clicked[0])
		assign_texture(state::clicked, clicked);
	if (hovered[0])
		assign_texture(state::hovered, hovered);
	if (disabled[0])
		assign_texture(state::disabled, disabled);
}

Button::btn::btn()
{
	visible = true;
	prototype = nullptr;
	sprite.setOrigin(0.f, 0.f);
	x = y = 0.f;
	width = height = 0;
	btn_state = state::def;
	a_void_void = nullptr;
	a_void_ptr = nullptr;
	atype = action_type::no;
}

Button::btn::btn(type* p)
{
	visible = true;
	prototype = p;
	sprite.setOrigin(0.f, 0.f);
	x = y = 0.f;
	width = prototype->texture[state::def]->getSize().x;
	height = prototype->texture[state::def]->getSize().y;
	btn_state = state::def;
	a_void_void = nullptr;
	a_void_ptr = nullptr;
	atype = action_type::no;
}

Button::btn::~btn()
{

}

Button::state Button::btn::get_state()
{
	return btn_state;
}

Button::state Button::btn::check_state_2(float mouse_x, float mouse_y, bool mouse_click, bool _set_state)
{
    state _state = state::def;
    if (!visible)
        _state = state::def;
    else
    {
        if (btn_state == state::disabled)
            _state = state::disabled;
        if ((mouse_x >= x) && (mouse_x <= x + width) && (mouse_y >= y) && (mouse_y <= y + height))
        {
            _state = state::hovered;
        }
    }
    if (_set_state)
        set_state(_state);
    return _state;
}

Button::state Button::btn::check_state(float mouse_x, float mouse_y, bool mouse_click, bool _set_state)
{
	state _state = state::def;
	if (!visible)
		_state = state::def;
	else
	{
		if (btn_state == state::disabled)
			_state = state::disabled;
		if ((mouse_x >= x) && (mouse_x <= x + width) && (mouse_y >= y) && (mouse_y <= y + height))
		{
			if (mouse_click)
			{
				_state = state::clicked;
				click();
			}
			else
				_state = state::hovered;
		}
	}
	if(_set_state)
		set_state(_state);
	return _state;
}

void Button::btn::set_state(state _state)
{
	btn_state = _state;
	if (prototype->state_exists[btn_state])
		sprite.setTexture(*(prototype->texture[btn_state]));
	else
		sprite.setTexture(*(prototype->texture[state::def]));
}

void Button::btn::onclick(void(*func)())
{
	a_void_void = func;
	atype = action_type::void_void;
}

void Button::btn::onclick(void(*func)(void*), void* ptr)
{
	a_void_ptr = func;
	atype = action_type::void_ptr;
	a_subject = ptr;
}

void Button::btn::click()
{
	switch (atype)
	{
	case action_type::void_void:
		if (a_void_void)
			(*a_void_void)();
		break;
	case action_type::void_ptr:
		if (a_void_ptr)
			(*a_void_ptr)(a_subject);
		break;
	}
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
	set_width(p->width);
	bounds = btn_text.getGlobalBounds();
}

Button::text::text(type* p, const char* _str) : btn(p)
{
	set_state(state::def);
	str = nullptr;
	set_text(_str);
	set_width(p->width);
}

Button::text::~text()
{
	if (str)
		delete[] str;
	// ~btn();
}

void Button::text::set_text(const char* _str)
{
	if (str)
		delete[] str;
	int len = 0;
	for (; _str[len]; len++);
	str = new char[len + 1];
	for (int i = 0; i < len; i++)
		str[i] = _str[i];
	str[len] = 0;
	btn_text.setString(str);
	bounds = btn_text.getGlobalBounds();
	btn_text.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
	btn_text.setPosition(x + width / 2.f, y + height / 2.f);
	bounds = btn_text.getGlobalBounds();
}

void Button::text::set_color(sf::Color color)
{
	btn_text.setFillColor(color);
}

void Button::text::set_size(unsigned size)
{
	btn_text.setCharacterSize(size);
	bounds = btn_text.getGlobalBounds();
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
	float shift_x = width / 2.f, shift_y = height / 2.f;
	x = _x;
	y = _y;
	sprite.setPosition(x, y);
	btn_text.setPosition(x + shift_x, y + shift_y);
}

void Button::text::set_width(int _width)
{
	if (_width <= 0)
		return;
	float factor = float(_width) / float(width);
	sprite.setScale(factor, factor);
	btn_text.setScale(factor, factor);
	width = _width;
	height = (int)(height * factor);
}

void Button::text::draw_in(sf::RenderWindow& window)
{
	if (!visible)
		return;
	window.draw(sprite);
	window.draw(btn_text);
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
	if (!visible)
		return;
	window.draw(sprite);
	window.draw(icon_sprite);
}
