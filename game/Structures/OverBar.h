#pragma once
#include <SFML/Graphics.hpp>

extern sf::RenderWindow window;
extern sf::View view;

namespace OverBar
{
	sf::Texture* textures[] = { 0, 0, 0, 0 };

	enum color
	{
		empty,
		blue,
		green,
		red
	};

	struct bar
	{
		sf::Sprite itself;
		sf::Sprite background;
		float percentage;

		int height = 28;
		int width = 206;

		bar();
		bar(color);
		~bar();

		void set_color(color);
		void set_percentage(float);
		void set_position(float, float);
		void set_width(float);
		void draw();
	};

	bar::bar()
	{
		percentage = 100.f;
	}

	bar::bar(color c)
	{
		set_color(c);
		percentage = 100.f;
	}

	bar::~bar()
	{

	}

	void bar::set_color(color c)
	{
		if (!textures[color::empty])
			textures[color::empty]->loadFromFile("Textures/bars/empty.png");
		if (!textures[c])
			switch (c)
			{
			case color::blue:
				textures[color::blue]->loadFromFile("Textures/bars/blue.png");
				break;
			case color::green:
				textures[color::green]->loadFromFile("Textures/bars/green.png");
				break;
			case color::red:
				textures[color::red]->loadFromFile("Textures/bars/red.png");
				break;
			}
		background.setTexture(*(textures[color::empty]));
		itself.setTexture(*(textures[c]));

		background.setOrigin(0.f, 28.f);
		itself.setOrigin(0.f, 28.f);
	}

	void bar::set_percentage(float percentage)
	{
		itself.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i((int)(width * percentage), height)));
	}

	void bar::set_position(float x, float y)
	{
		background.setPosition(x, y);
		itself.setPosition(x, y);
	}

	void bar::set_width(float w)
	{
		float factor = w / (float)width;
		background.setScale(factor, (float)height * factor);
	}

	void bar::draw()
	{
		window.draw(background);
		window.draw(itself);
	}
};