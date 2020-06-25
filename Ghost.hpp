#pragma once
#include <SFML/Graphics.hpp>
#include<random>
#include<vector>
#include<algorithm>
#include "Stage.hpp"
#include "Player.hpp"

using namespace sf;
using namespace std;

class Ghost
{
public:
    Ghost();

    void move(Stage &stage, Player& player);
    void draw(RenderTarget& window);
    void trigger_scared();
    void trigger_killed();
    void reset();

    float coord_x,coord_y;
    int mode=0;


protected:

    virtual void move_scatter(Stage& stage){}
    virtual void move_chase(Stage& stage, Player& player){}
    void move_frightened(Stage &stage);
    void move_killed(Stage &stage);
    bool move_out_of_box();
    bool move_in_special_cells();
    void move_by_fact(float x);

    bool middle();
    float dist(float a,float b,float c,float d);
    float start_coord_x,start_coord_y;
    void make_coords_divisible(float x);

    vector<pair<float,float>> special_cells = { {8*30+15,10*30+15} , {10*30+15,10*30+15} , {8*30+15,18*30+15} , {10*30+15,18*30+15} };
    int last_move=0;
    int timer_scared=0;
    int timer=0;

    Texture img_source;
    Sprite ghost_img;
    Texture scared_source;
    Sprite scared_img;
    Texture eyes_source;
    Sprite eyes_img;
    Texture scared2_source;
    Sprite scared2_img;
};
