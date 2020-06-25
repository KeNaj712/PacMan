#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Heart
{
public:
    Heart();
    int cnt=3;
    void draw(RenderTarget& window);
    void reset();
private:
    Texture heart_source;
    Sprite heart_img;
};
