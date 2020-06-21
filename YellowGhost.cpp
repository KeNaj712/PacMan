#include "YellowGhost.hpp"

YellowGhost::YellowGhost()
{
    coord_x=9*30+15;
    coord_y=12*30+15;
    start_coord_x=coord_x;
    start_coord_y=coord_y;
    img_source.loadFromFile("images/yellow_ghost_img.png");
    ghost_img.setTexture(img_source);
    ghost_img.scale({0.05,0.05});
    ghost_img.setOrigin(300,300);
}

void YellowGhost::move_scatter(Stage& stage)
{
    make_coords_divisible(1.875);
    if(move_out_of_box())
        return;
    if(middle())
    {
        vector<pair<float,int>> v;

        if(stage.free(coord_x+30,coord_y))
            v.push_back(make_pair(dist(coord_x+30,coord_y,45,24*30+15),0));
        if(stage.free(coord_x,coord_y+30))
            v.push_back(make_pair(dist(coord_x,coord_y+30,45,24*30+15),1));
        if(stage.free(coord_x-30,coord_y))
            v.push_back(make_pair(dist(coord_x-30,coord_y,45,24*30+15),2));
        if(stage.free(coord_x,coord_y-30))
            v.push_back(make_pair(dist(coord_x,coord_y-30,45,24*30+15),3));

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

void YellowGhost::move_chase(Stage& stage, Player& player)
{
    make_coords_divisible(1.875);
    if(move_out_of_box())
        return;
    if(dist(coord_x,coord_y,player.coord_x,player.coord_y)<=(4*30)*(4*30))
    {
        move_scatter(stage);
        return;
    }
    if(middle())
    {
        vector<pair<float,int>> v;
        float target_x=player.coord_x,target_y=player.coord_y;
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




