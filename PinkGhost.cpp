#include "PinkGhost.hpp"

PinkGhost::PinkGhost()
{
    coord_x=10*30+15-1.875;
    coord_y=12*30+15;
    start_coord_x=coord_x;
    start_coord_y=coord_y;
    img_source.loadFromFile("images/pink_ghost_img.png");
    ghost_img.setTexture(img_source);
    ghost_img.scale({0.05,0.05});
    ghost_img.setOrigin(300,300);
}

void PinkGhost::move_scatter(Stage& stage)
{
    make_coords_divisible(1.875);
    if(move_out_of_box())
        return;
    if(middle())
    {
        vector<pair<float,int>> v;

        if(stage.free(coord_x+30,coord_y))
            v.push_back(make_pair(dist(coord_x+30,coord_y,45,45),0));
        if(stage.free(coord_x,coord_y+30))
            v.push_back(make_pair(dist(coord_x,coord_y+30,45,45),1));
        if(stage.free(coord_x-30,coord_y))
            v.push_back(make_pair(dist(coord_x-30,coord_y,45,45),2));
        if(stage.free(coord_x,coord_y-30))
            v.push_back(make_pair(dist(coord_x,coord_y-30,45,45),3));

        sort(v.begin(),v.end());
        for(auto x:v)
            if(abs(x.second-last_move)!=2)
            {
                last_move=x.second;
                break;
            }
    }
    move_by_fact(1.875);
}

void PinkGhost::move_chase(Stage& stage, Player& player)
{
    make_coords_divisible(1.875);
    if(move_out_of_box())
        return;
    if(middle())
    {
        vector<pair<float,int>> v;
        float target_x=player.coord_x,target_y=player.coord_y;
        if(player.move_now==0)
            target_x+=90;
        if(player.move_now==1)
            target_y+=90;
        if(player.move_now==2 || player.move_now==3)
            target_x-=90;
        if(player.move_now==3)
            target_y-=90;
        if(stage.free(coord_x+30,coord_y))
            v.push_back(make_pair(dist(coord_x+30,coord_y,target_x,target_y),0));
        if(stage.free(coord_x,coord_y+30))
            v.push_back(make_pair(dist(coord_x,coord_y+30,target_x,target_y),1));
        if(stage.free(coord_x-30,coord_y))
            v.push_back(make_pair(dist(coord_x-30,coord_y,target_x,target_y),2));
        if(stage.free(coord_x,coord_y-30))
            v.push_back(make_pair(dist(coord_x,coord_y-30,target_x,target_y),3));

        sort(v.begin(),v.end());
        for(auto x:v)
            if(abs(x.second-last_move)!=2)
            {
                last_move=x.second;
                break;
            }
    }
    move_by_fact(1.875);
}




