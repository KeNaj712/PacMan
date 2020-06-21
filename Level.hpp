#pragma once
#include <SFML\Graphics.hpp>
#include <string>
using namespace sf;
using namespace std;

class Level
{
public:
    Level();
    void next();
    void draw(RenderTarget& window);
    void reset();
private:
    Font font;
    int level=1;
};
