#pragma once
#include <SFML/Graphics.hpp>
#include "Player.hpp"
using namespace sf;

class Bonus
{

public:
    Bonus(float x,float y);
    void draw(RenderTarget& window);
    float coord_x,coord_y;
    int timer=0;

private:
    CircleShape shape;
};
