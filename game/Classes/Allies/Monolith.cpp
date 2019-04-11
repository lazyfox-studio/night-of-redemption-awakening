#include "../../Headers/Allies/Monolith.h"

Monolith::Monolith() : Ally((float)screen.w / 2.0f + 400, (float)screen.h / 2.0f + 400, 200, 0.0f, 0)
{
	sprite.assign_texture("Textures/monolith.png", SPRITE_SIZE, SPRITE_SIZE);
	sprite.set_origin(SPRITE_SIZE / 2.0f, SPRITE_SIZE / 2.0f);
	sprite.set_position(x, y);
}

Monolith::~Monolith()
{
}

void Monolith::move(float dbx, float dby, List<Unit>& units, bool is_shift)
{

}
