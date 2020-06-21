#include "Heart.hpp"

Heart::Heart()
{
    heart_source.loadFromFile("images/player_img.png");
    heart_img.setTexture(heart_source);
    heart_img.scale({0.05,0.05});
    heart_img.setOrigin(270,300.5);
}

void Heart::draw(RenderTarget& window)
{
    float coord_x=30;
    for(int y=0;y<cnt;y++)
    {
        heart_img.setPosition({coord_x,30});
        window.draw(heart_img);
        coord_x+=40;
    }
}

void Heart::reset()
{
    cnt=3;
}
