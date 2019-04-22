#include "..\Headers\MSprite.h"

MSprite::MSprite()
{
	texture = new sf::Texture;
	frames = 0;
	current_frame = 0;
}

MSprite::~MSprite()
{
}

void MSprite::set_origin(float x, float y)
{
	sprite.setOrigin(sf::Vector2f(x, y));
}

void MSprite::set_position(float x, float y)
{
	sprite.setPosition(x, y);
}

void MSprite::move(float dx, float dy)
{
	sprite.move(dx, dy);
}

void MSprite::rotate(float deg)
{
	sprite.rotate(deg);
}

void MSprite::set_rotation(float deg)
{
	sprite.setRotation(deg);
}

void MSprite::set_color(sf::Color color)
{
	sprite.setColor(color);
}

void MSprite::draw_in(sf::RenderWindow& window)
{
	window.draw(sprite);
}

void MSprite::assign_texture(const char* file, int _frames, int _frame_width, int _frame_height)
{
	texture->loadFromFile(file);
	assign_texture(texture, _frames, _frame_width, _frame_height);
}

void MSprite::assign_texture(sf::Texture* _texture, int _frames, int _frame_width, int _frame_height)
{
	frames = _frames;
	frame_width = _frame_width;
	frame_height = _frame_height;
	texture = _texture;
	texture->setSmooth(true);
	sprite.setTexture(*texture);
	sprite.setTextureRect(sf::IntRect(0, 0, _frame_width, _frame_height));
	current_frame = 0;
}

void MSprite::assign_texture(const char* file, int _frame_width, int _frame_height)
{
	assign_texture(file, 1, _frame_width, _frame_height);
}

void MSprite::assign_texture(sf::Texture* _texture, int _frame_width, int _frame_height)
{
	assign_texture(texture, 1, _frame_width, _frame_height);
}

void MSprite::assign_texture(sf::Texture* _texture)
{
	frames = 1;
	texture = _texture;
	texture->setSmooth(true);
	sprite.setTexture(*texture);
	frame_width = texture->getSize().x;
	frame_height = texture->getSize().y;
	current_frame = 0;
}

void MSprite::assign_texture(const char* file)
{
	texture->loadFromFile(file);
	assign_texture(texture);
}

void MSprite::set_frame(int frame)
{
	if (frame >= frames)
		return;
	current_frame = frame;
	sprite.setTextureRect(sf::IntRect(frame * frame_width, 0, frame_width, frame_height));
}

void MSprite::next_frame()
{
	current_frame = current_frame + 1 >= frames ? 0 : current_frame + 1;
	set_frame(current_frame);
}

int MSprite::get_frame()
{
	return current_frame;
}
