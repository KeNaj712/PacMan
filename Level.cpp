#include "Level.hpp"

Level::Level()
{
    font.loadFromFile("fonts/joystix_monospace.ttf");
}

void Level::next()
{
    level++;
}

void Level::draw(RenderTarget& window)
{
    int pom=level;
    string lvl_num="";
    while(pom!=0)
    {
        lvl_num+=('0'+(pom%10));
        pom/=10;
    }
    reverse(lvl_num.begin(),lvl_num.end());
    Text text(lvl_num,font);
    text.setCharacterSize(40);
    text.setPosition(269-((lvl_num.size()-1)*15),5);
    window.draw(text);
}

void Level::reset()
{
    level=1;
}
