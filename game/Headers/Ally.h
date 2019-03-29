#pragma once
#include <SFML/Graphics.hpp>

extern sf::RenderWindow window;
extern sf::View view;

class Ally
{
    friend class Enemy;
protected:
    float x;
    float y;
    int health;

public:
    Ally()
    {

    }
    ~Ally()
    {

    }

    virtual void draw() = 0;
};