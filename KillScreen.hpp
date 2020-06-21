#pragma once
#include <SFML\Graphics.hpp>
#include "Player.hpp"
using namespace sf;
class KillScreen
{
public:
    void run(Player& player,Ghost& ghost,Score& score);
private:

};
