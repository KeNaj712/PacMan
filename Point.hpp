#pragma once
#include <SFML/Graphics.hpp>
#include "Player.hpp"
class Point
{

public:
    Point(float x,float y);
    void draw(RenderTarget& window);
    float coord_x,coord_y;
private:
    RectangleShape shape;
    int val=10;
};
