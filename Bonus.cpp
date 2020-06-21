#include "Bonus.hpp"

Bonus::Bonus(float x,float y)
{
    coord_x=x;
    coord_y=y;
    shape.setOrigin(7,7);
    shape.setRadius(7);
    shape.setPosition({x,y});
    shape.setFillColor(Color(247,173,142));
}

void Bonus::draw(RenderTarget& window)
{
    if(timer%22<11 || timer<0)
        window.draw(shape);
    timer++;
}

