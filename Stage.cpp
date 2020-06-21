#include"Stage.hpp"

Stage::Stage()
{
    ifstream infile("txt_files/stage.txt");
    for(int x=0;x<24;x++)
        for(int y=0;y<19;y++)
            infile>>block[x][y];
}

void Stage::draw(RenderTarget& window)
{
    RectangleShape square;
    square.setFillColor(Color::Blue);
    square.setSize({blockSize,blockSize});
    for(int x=0;x<24;x++)
        for(int y=0;y<19;y++)
        {
            if(block[x][y]==1)
            {
                square.setPosition({blockSize*y,blockSize*x});
                window.draw(square);
            }
            if(block[x][y]==2)
            {
                square.setPosition({blockSize*y,blockSize*x+12});
                square.setSize({blockSize,6});
                square.setFillColor(Color::White);
                window.draw(square);
                square.setFillColor(Color::Blue);
                square.setSize({blockSize,blockSize});
            }
        }
}

bool Stage::free(float x,float y)
{
    if(y==375 && (x<40 || x>420) && x>=-30 && x<=600)
        return true;
    if(x<0 || x>=570)
        return false;
    int pom1=y,pom2=x;
    return (block[pom1/30][pom2/30]==0);
}

bool Stage::free_or_gate(float x,float y)
{
    if(y==375 && (x<40 || x>420) && x>=-30 && x<=600)
        return true;
    if(x<0 || x>=570)
        return false;
    int pom1=y,pom2=x;
    return (block[pom1/30][pom2/30]==0 || block[pom1/30][pom2/30]==2);
}
