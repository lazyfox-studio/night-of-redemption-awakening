#pragma once
#include <SFML/Graphics.hpp>

class MSprite
{
	sf::Sprite sprite;
	sf::Texture* texture;
	int frame_width;
	int frame_height;
	int frames;
	int current_frame;

public:
	MSprite();
	~MSprite();

	void set_origin(float, float);
	void set_position(float, float);
	void move(float, float);
	void rotate(float);
	void set_rotation(float);
	void set_color(sf::Color);
	void draw_in(sf::RenderWindow&);

	void assign_texture(const char* file, int _frames, int _frame_width, int _frame_height);
	void assign_texture(sf::Texture* _texture, int _frames, int _frame_width, int _frame_height);
	void assign_texture(const char* file, int _frame_width, int _frame_height);
	void assign_texture(sf::Texture* _texture, int _frame_width, int _frame_height);
	void assign_texture(sf::Texture* _texture);
	void assign_texture(const char* file);
	void set_frame(int);
	void next_frame();

	int get_frame();
};