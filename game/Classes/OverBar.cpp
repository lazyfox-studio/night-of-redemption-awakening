#include "../Headers/OverBar.h"

namespace OverBar
{
	sf::Texture* textures[4] = { 0, 0, 0, 0 };
}

OverBar::bar::bar()
{
	percentage = 1.f;
	col = color::empty;
}

OverBar::bar::bar(color c)
{
	set_color(c);
	percentage = 1.f;
}

OverBar::bar::~bar()
{

}

void OverBar::bar::set_color(color c)
{
	if (!textures[color::empty])
	{
		textures[color::empty] = new sf::Texture;
		textures[color::empty]->loadFromFile("Textures/bars/empty.png");
	}
	if (!textures[c])
		switch (c)
		{
		case color::blue:
			textures[color::blue] = new sf::Texture;
			textures[color::blue]->loadFromFile("Textures/bars/blue.png");
			break;
		case color::green:
			textures[color::green] = new sf::Texture;
			textures[color::green]->loadFromFile("Textures/bars/green.png");
			break;
		case color::red:
			textures[color::red] = new sf::Texture;
			textures[color::red]->loadFromFile("Textures/bars/red.png");
			break;
		default:
			return;
		}
	background.setTexture(*(textures[color::empty]));
	itself.setTexture(*(textures[c]));
	background.setOrigin(0.f, 28.f);
	itself.setOrigin(0.f, 28.f);
	col = c;
}

void OverBar::bar::set_percentage(float percentage)
{
	background.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(width, height)));
	itself.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i((int)(width * percentage), height)));
}

void OverBar::bar::set_position(float x, float y)
{
	background.setPosition(x, y);
	itself.setPosition(x, y);
}

void OverBar::bar::set_width(float w)
{
	float factor = w / (float)width;
	background.setScale(factor, factor);
	itself.setScale(factor, factor);
}

OverBar::color OverBar::bar::get_color()
{
	return col;
}

float OverBar::bar::get_percentage()
{
	return percentage;
}

void OverBar::bar::draw_in(sf::RenderWindow& window)
{
	window.draw(background);
	window.draw(itself);
}
