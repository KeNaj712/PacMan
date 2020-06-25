#pragma once
#include <SFML/Graphics.hpp>
#include "Stage.hpp"
#include "Ghost.hpp"
using namespace sf;

class RedGhost : public Ghost
{
public:
    RedGhost();
    virtual void move_scatter(Stage& stage);
    virtual void move_chase(Stage& stage, Player& player);
};
