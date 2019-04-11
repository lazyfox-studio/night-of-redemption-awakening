#include "../../Headers/Allies/Monolith.h"

Monolith::Monolith() : Ally((float)screen.w / 2.0f + 400, (float)screen.h / 2.0f + 400, 200, 0.0f, 0)
{
	texture->loadFromFile("Textures/monolith.png");
	texture->setSmooth(true);
	sprite.setTexture(*texture);
	sprite.setTextureRect(sf::IntRect(0, 0, SPRITE_SIZE, SPRITE_SIZE));
	sprite.setOrigin(sf::Vector2f(SPRITE_SIZE / 2.0f, SPRITE_SIZE / 2.0f));
	sprite.setPosition(x, y);
}

Monolith::~Monolith()
{
}

void Monolith::move(float dbx, float dby, List<Unit>& units, bool is_shift)
{

}
