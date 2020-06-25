#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>

using namespace sf;
using namespace std;

class Stage
{
public:
    Stage();
    void draw(RenderTarget& window);
    bool free(float x,float y);
    bool free_or_gate(float x,float y);
private:
    Sprite background;
    int block[24][19];
    float blockSize=30;

};
