#include "Score.hpp"

Score::Score()
{
    font.loadFromFile("fonts/joystix_monospace.ttf");
}

void Score::update(int a)
{
    score+=a;
}

string Score::get_score()
{
    string score_string="";
    int pom=score;
    for(int x=0;x<6 || pom!=0;x++)
    {
        score_string+=('0'+(pom%10));
        pom/=10;
    }
    reverse(score_string.begin(),score_string.end());
    return score_string;
}

void Score::draw(RenderTarget& window)
{
    string score_string=get_score();
    Text text(score_string,font);
    text.setCharacterSize(30);
    text.setPosition(415-((int)score_string.size()-6)*27,10);
    window.draw(text);
}

void Score::reset()
{
    score=0;
}
