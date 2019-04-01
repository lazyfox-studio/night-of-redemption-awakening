#include "../../Headers/Allies/Person.h"

void Person::shoot() {

}

void Person::draw() {
	window.draw(sprite);
}

void Person::move(float dbx, float dby, bool is_shift)
{
	float shift = is_shift ? 1.f : 0.f;
	if ((dbx != 0) && (dby != 0)) //Чтобы бег по диагонали не был быстрее чем по прямой
	{
		float dx = dbx * (speed + (speed * shift)) * 0.707f;
		float dy = dby * (speed + (speed * shift)) * 0.707f;
		if (is_out_of_terrain(dx, dy))
			return;
		x = x + dx;
		y = y + dy;
		view.move(dx, dy);
		sprite.move(dx, dy);
		return;
	}
	float dx = dbx * (speed + (speed * shift));
	float dy = dby * (speed + (speed * shift));
	if (is_out_of_terrain(dx, dy))
		return;
	x = x + dx;
	y = y + dy;
	view.move(dx, dy);
	sprite.move(dx, dy);
}
