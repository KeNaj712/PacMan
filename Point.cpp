#include "Point.hpp"

Point::Point(float x,float y)
{
    coord_x=x;
    coord_y=y;
    shape.setSize({3,3});
    shape.setOrigin(1.5,1.5);
    shape.setPosition({x,y});
    shape.setFillColor(Color(247,173,142));
}

void Point::draw(RenderTarget& window)
{
    window.draw(shape);
}

