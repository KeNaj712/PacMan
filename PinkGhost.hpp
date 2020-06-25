#pragma once
#include <SFML/Graphics.hpp>
#include "Stage.hpp"
#include "Ghost.hpp"
using namespace sf;

class PinkGhost : public Ghost
{
public:
    PinkGhost();
    virtual void move_scatter(Stage& stage);
    virtual void move_chase(Stage& stage, Player& player);
};
