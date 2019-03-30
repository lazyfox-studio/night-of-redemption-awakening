#include "../../Headers/Allies/Person.h"

void Person::move_d() {
    int dbx = 0, dby = 0, shift = 0;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        dbx += -1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        dbx += 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        dby += -1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        dby += 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
    {
        shift = 1;
    }

    if ((dbx != 0) && (dby != 0)) //Чтобы бег по диагонали не был быстрее чем по прямой
    {
        float dx = dbx * (speed + (speed * shift)) * 0.707f;
        float dy = dby * (speed + (speed * shift)) * 0.707f;
        x = x + dx;
        y = y + dy;
        view.move(dx, dy);
        return;
    }
    float dx = dbx * (speed + (speed * shift));
    float dy = dby * (speed + (speed * shift));
    x = x + dx;
    y = y + dy;
    view.move(dx, dy);
}

void Person::shoot() {

}

void Person::draw() {
	window.draw(sprite);
}

void Person::rotate(float deg)
{
	sprite.rotate(deg);
	pov += deg;
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

bool Person::is_out_of_terrain(float dx, float dy)
{
	return (x + dx <= 0) || (x + dx >= screen.w) || (y + dy <= 0) || (y + dy >= screen.h);
}
