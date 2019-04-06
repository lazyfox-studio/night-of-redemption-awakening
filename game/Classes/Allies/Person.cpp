#include "../../Headers/Allies/Person.h"

Person::Person() : Ally((float)screen.w / 2.0f, (float)screen.h / 2.0f, 200, 3.0f, 0.0f)
{
	texture->loadFromFile("Textures/player.png");
	texture->setSmooth(true);
	sprite.setTexture(*texture);
	sprite.setTextureRect(sf::IntRect(0, 0, SPRITE_SIZE, SPRITE_SIZE));
	sprite.setOrigin(sf::Vector2f(SPRITE_SIZE / 2.0f, SPRITE_SIZE / 2.0f));
	sprite.setPosition(x, y);
}

Person::~Person()
{
}

void Person::shoot(List<Enemy>& enemies) {
    ListItem<Enemy>* target = nullptr;
    float range = INT_MAX;
    float _x, _y;
    for (ListItem<Enemy>* i = enemies.head; i; i = i->next)
    {
        _x = i->value->x;
        _y = i->value->y;
        switch (pov)
        {
        case 0:
            if ((_x - SPRITE_SIZE / 2 < x) && (_x + SPRITE_SIZE / 2 > x) && (_y > y))
            {
                if (i->value->r < range)
                {
                    target = i;
                    range = target->value->r;
                }
            }
            break;
        case 180:
            if ((_x - SPRITE_SIZE / 2 < x) && (_x + SPRITE_SIZE / 2 > x) && (_y < y))
            {
                if (i->value->r < range)
                {
                    target = i;
                    range = target->value->r;
                }
            }
            break;
        case 90:
            if ((_y - SPRITE_SIZE / 2 < y) && (_y + SPRITE_SIZE / 2 > y) && (_x < x))
            {
                if (i->value->r < range)
                {
                    target = i;
                    range = target->value->r;
                }
            }
            break;
        case -90:
            if ((_y - SPRITE_SIZE / 2 < y) && (_y + SPRITE_SIZE / 2 > y) && (_x < x))
            {
                if (i->value->r < range)
                {
                    target = i;
                    range = target->value->r;
                }
            }
            break;
        case -45:
            if ((_y - SPRITE_SIZE / 2 < (y - _x + x)) && (_y + SPRITE_SIZE / 2 > (y - _x + x)) && (_x > x))
            {
                if (i->value->r < range)
                {
                    target = i;
                    range = target->value->r;
                }
            }
            break;
        case 45:
            if ((_y - SPRITE_SIZE / 2 < (y + _x - x)) && (_y + SPRITE_SIZE / 2 > (y + _x - x)) && (_x < x))
            {
                if (i->value->r < range)
                {
                    target = i;
                    range = target->value->r;
                }
            }
            break;
        case 135:
            if ((_y - SPRITE_SIZE / 2 < (y - _x + x)) && (_y + SPRITE_SIZE / 2 > (y - _x + x)) && (_x < x))
            {
                if (i->value->r < range)
                {
                    target = i;
                    range = target->value->r;
                }
            }
        case -135:
            if ((_y - SPRITE_SIZE / 2 < (y + _x - x)) && (_y + SPRITE_SIZE / 2 > (y + _x - x)) && (_x > x))
            {
                if (i->value->r < range)
                {
                    target = i;
                    range = target->value->r;
                }
            }
            break;
        }
    }
    if (range != INT_MAX)
    {
        target->value->health -= 5; //ALARM ПОМЕНЯТЬ НА ЗНАЧЕНИЕ УРОНА!!!!!!!!!!!!!!!!!
    }
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
	//bool out_of_terrain = is_out_of_terrain(dx, dy);
	//bool on_edge = is_edge_of_terrain(dx, dy);
	if (is_out_of_terrain(dx, dy))
		return;
	x = x + dx;
	y = y + dy;
	view.move(dx, dy);
	sprite.move(dx, dy);
}
