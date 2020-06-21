#include "Player.hpp"

Player::Player()
{
    player_source.loadFromFile("images/player_img.png");
    player_img.setTexture(player_source);
    player_img.scale({0.04,0.04});
    player_img.setOrigin(270,300.5);
    player_killed_source.loadFromFile("images/player_killed_img.png");
    player_killed_img.setTexture(player_killed_source);
    player_killed_img.scale({0.04,0.04});
    player_killed_img.setOrigin(270,300.5);
}

void Player::draw(RenderTarget& window)
{
    if(killed)
    {
        player_killed_img.setPosition({coord_x,coord_y});
        window.draw(player_killed_img);
        return;
    }
    player_img.setPosition({coord_x,coord_y});
    if(move_now==0)
    {
        window.draw(player_img);
    }
    if(move_now==1)
    {
        player_img.rotate(90);
        window.draw(player_img);
        player_img.rotate(270);
    }
    if(move_now==2)
    {
        player_img.rotate(180);
        window.draw(player_img);
        player_img.rotate(180);
    }
    if(move_now==3)
    {
        player_img.rotate(270);
        window.draw(player_img);
        player_img.rotate(90);
    }
    if(timer%20>=10 && timer>=0)
    {
        if(move_now==0)
        {
            player_img.rotate(180);
            player_img.setPosition({coord_x+1,coord_y});
            window.draw(player_img);
            player_img.setPosition({coord_x-1,coord_y});
            player_img.rotate(180);
        }
        if(move_now==1)
        {
            player_img.rotate(270);
            player_img.setPosition({coord_x,coord_y+1});
            window.draw(player_img);
            player_img.setPosition({coord_x,coord_y-1});
            player_img.rotate(90);
        }
        if(move_now==2)
        {
            player_img.setPosition({coord_x-1,coord_y});
            window.draw(player_img);
            player_img.setPosition({coord_x+1,coord_y});
        }
        if(move_now==3)
        {
            player_img.rotate(90);
            player_img.setPosition({coord_x,coord_y-1});
            window.draw(player_img);
            player_img.setPosition({coord_x,coord_y+1});
            player_img.rotate(270);
        }
    }
    timer++;
}

void Player::move(Stage& stage)
{
    if(Keyboard::isKeyPressed(Keyboard::Right))
        move_queue=0;
    if(Keyboard::isKeyPressed(Keyboard::Down))
        move_queue=1;
    if(Keyboard::isKeyPressed(Keyboard::Left))
        move_queue=2;
    if(Keyboard::isKeyPressed(Keyboard::Up))
        move_queue=3;

    if((4+move_now-move_queue)%4==2)
        move_now=move_queue;
    else if((4+move_now-move_queue)%2==1 && middle())
    {
        if(move_queue==0 && stage.free(coord_x+20,coord_y))
            move_now=move_queue;
        if(move_queue==1 && stage.free(coord_x,coord_y+20))
            move_now=move_queue;
        if(move_queue==2 && stage.free(coord_x-20,coord_y))
            move_now=move_queue;
        if(move_queue==3 && stage.free(coord_x,coord_y-20))
            move_now=move_queue;
    }

    if(move_now==0 && stage.free(coord_x+16,coord_y))
        coord_x+=1.875;
    if(move_now==1 && stage.free(coord_x,coord_y+16))
        coord_y+=1.875;
    if(move_now==2 && stage.free(coord_x-16,coord_y))
        coord_x-=1.875;
    if(move_now==3 && stage.free(coord_x,coord_y-16))
        coord_y-=1.875;
    if(coord_x==-15)
        coord_x=585;
    else if(coord_x==585)
        coord_x=-15;
}

void Player::reset()
{
    coord_x=30*9+15;
    coord_y=30*18+15;
    move_now=3;
    move_queue=3;
    timer=0;
    killed=false;
}

bool Player::middle()
{
    int pom1=coord_x,pom2=coord_y;
    if(pom1%30==15 && pom2%30==15)
        return true;
    return false;
}
