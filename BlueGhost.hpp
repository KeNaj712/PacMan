#pragma once
#include <SFML/Graphics.hpp>
#include "Stage.hpp"
#include "Ghost.hpp"
#include "RedGhost.hpp"
using namespace sf;

class BlueGhost : public Ghost
{
public:
    BlueGhost();
    virtual void move_scatter(Stage& stage);
    virtual void move_chase(Stage& stage, Player& player);
    void update_red_coords(RedGhost& ghost);
private:
    float red_coord_x,red_coord_y;
};
