#include "Ghost.hpp"

Ghost::Ghost()
{
    scared_source.loadFromFile("images/scared_ghost_img.png");
    scared_img.setTexture(scared_source);
    scared_img.scale({0.057,0.057});
    scared_img.setOrigin(256,256);
    scared2_source.loadFromFile("images/scared_ghost_2_img.png");
    scared2_img.setTexture(scared2_source);
    scared2_img.scale({0.057,0.057});
    scared2_img.setOrigin(256,256);
    eyes_source.loadFromFile("images/eyes_img.png");
    eyes_img.setTexture(eyes_source);
    eyes_img.scale({0.055,0.055});
    eyes_img.setOrigin(210,210);
}

///-------------main move functions------------------///

void Ghost::move(Stage& stage, Player& player)
{
    timer++;
    if(move_in_special_cells())
        return;

    if(mode==0)
        move_scatter(stage);
    else if(mode==1)
        move_chase(stage,player);
    else if(mode==2)
    {
        move_frightened(stage);
        timer_scared--;
        if(timer_scared==0)
            mode=0;
    }
    else if(mode==3)
    {
        move_killed(stage);
        if(dist(coord_x,coord_y,285,375)==0)
            mode=0;
    }
    if(mode<2)
    {
        //int prev_mode=mode;
        if(timer<2*20*60)
        {
            if((timer%(20*60))<=(5*60))
                mode=0;
            else
                mode=1;
        }
        else
        {
            if((timer%(15*60))<=(4*60))
                mode=0;
            else
                mode=1;
        }
        //if(prev_mode!=mode)
        //   last_move=(last_move+2)%4;
    }
}

void Ghost::move_frightened(Stage& stage)
{
    make_coords_divisible(1);
    if(middle())
    {
        int pom;
        while(true)
        {
            pom=rand()%4;
            while(abs(pom-last_move)==2)
                pom=rand()%4;
            if(pom==0 && !stage.free(coord_x+30,coord_y))
                continue;
            if(pom==1 && !stage.free(coord_x,coord_y+30))
                continue;
            if(pom==2 && !stage.free(coord_x-30,coord_y))
                continue;
            if(pom==3 && !stage.free(coord_x,coord_y-30))
                continue;
            break;
        }
        last_move=pom;
    }

    move_by_fact(1);
}

void Ghost::move_killed(Stage& stage)
{
    make_coords_divisible(3);
    if(middle())
    {
        vector<pair<float,int>> v;

        if(stage.free_or_gate(coord_x+30,coord_y))
            v.push_back(make_pair(dist(coord_x+30,coord_y,285,375),0));
        if(stage.free_or_gate(coord_x,coord_y+30))
            v.push_back(make_pair(dist(coord_x,coord_y+30,285,375),1));
        if(stage.free_or_gate(coord_x-30,coord_y))
            v.push_back(make_pair(dist(coord_x-30,coord_y,285,375),2));
        if(stage.free_or_gate(coord_x,coord_y-30))
            v.push_back(make_pair(dist(coord_x,coord_y-30,285,375)-0.1,3));

        sort(v.begin(),v.end());
        for(auto x:v)
            if(abs(x.second-last_move)!=2)
            {
                last_move=x.second;
                break;
            }
    }
    move_by_fact(3);
}

///--------move functions - special cases----------///

void Ghost::move_by_fact(float x)
{
    if(last_move==0)
        coord_x+=x;
    if(last_move==1)
        coord_y+=x;
    if(last_move==2)
        coord_x-=x;
    if(last_move==3)
        coord_y-=x;
    if(coord_x==-15)
        coord_x=585;
    else if(coord_x==585)
        coord_x=-15;
}

bool Ghost::move_in_special_cells()
{
    bool cond=false;
    for(auto x:special_cells)
        if(x==make_pair(coord_x,coord_y))
            cond=true;
    if(cond)
    {
        if(last_move==1)
            return false;
        move_by_fact(1.875);
    }
    return cond;
}

bool Ghost::move_out_of_box()
{
    if(coord_x==285 && coord_y<=375 && coord_y>315)
    {
        last_move=3;
        move_by_fact(1.875);
        return true;
    }
    if(coord_y==375 && coord_x>=255 && coord_x<=315)
    {
        if(coord_x<285)
            last_move=0;
        else
            last_move=2;
        move_by_fact(1.875);
        return true;
    }
    return false;
}

///-------------helpful functions------------------///

bool Ghost::middle()
{
    int pom1=coord_x,pom2=coord_y;
    if(pom1%30==15 && pom2%30==15)
        return true;
    return false;
}

void Ghost::make_coords_divisible(float x)
{
    float pom=coord_x;
    while(pom<0)
        pom+=x;
    while(pom>=0)
        pom-=x;
    pom+=x;
    if(pom!=0)
        coord_x-=(pom-x);
    pom=coord_y;
     while(pom<0)
        pom+=x;
    while(pom>=0)
        pom-=x;
    pom+=x;
    if(pom!=0)
        coord_y-=(pom-x);
}

float Ghost::dist(float a,float b,float c,float d)
{
    return (a-c)*(a-c)+(b-d)*(b-d);
}

void Ghost::trigger_scared()
{
    if(mode!=3 && !(coord_x==285 && coord_y<=375 && coord_y>315) && !(coord_y==375 && coord_x>=255 && coord_x<=315))
    {
        if(mode!=2)
            last_move=(last_move+2)%4;
        mode=2;
        timer_scared=8*60;
    }
}

void Ghost::trigger_killed()
{
    mode=3;
    timer_scared=0;
}

void Ghost::reset()
{
    mode=0;
    last_move=0;
    timer=0;
    coord_x=start_coord_x;
    coord_y=start_coord_y;
}


///-------------draw------------------///

void Ghost::draw(RenderTarget& window)
{
    if(mode==0 || mode==1)
    {
        ghost_img.setPosition(coord_x,coord_y);
        window.draw(ghost_img);
    }
    else if(mode==2)
    {
        if(timer_scared>=3*60 || timer_scared%30<15)
        {
            scared_img.setPosition(coord_x,coord_y);
            window.draw(scared_img);
        }
        else
        {
            scared2_img.setPosition(coord_x,coord_y);
            window.draw(scared2_img);
        }

    }
    else if(mode==3)
    {
        eyes_img.setPosition(coord_x,coord_y);
        window.draw(eyes_img);
    }
}


