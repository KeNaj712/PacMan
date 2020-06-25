#pragma once
#include <SFML/Graphics.hpp>
#include "Stage.hpp"
using namespace sf;

class Player
{
public:
    Player();
    void draw(RenderTarget& window);
    void move(Stage &stage);
    void reset();

    float coord_x=30*9+15,coord_y=30*18+15;
    int move_now=3;
    int timer=0;
    bool killed=false;
private:

    int move_queue=3;

    Texture player_source;
    Sprite player_img;
    Texture player_killed_source;
    Sprite player_killed_img;

    bool middle();
};
