#pragma once
#include <SFML\Graphics.hpp>
#include <string>
using namespace sf;
using namespace std;

class Score
{
public:
    Score();
    void draw(RenderTarget& window);
    void update(int a);
    string get_score();
    void reset();
private:
    int score=0;
    Font font;

};
