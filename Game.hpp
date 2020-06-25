#pragma once
#include <SFML/Graphics.hpp>
#include <set>
#include <fstream>
#include "Stage.hpp"
#include "Player.hpp"
#include "RedGhost.hpp"
#include "PinkGhost.hpp"
#include "YellowGhost.hpp"
#include "BlueGhost.hpp"
#include "Bonus.hpp"
#include "Point.hpp"
#include "Heart.hpp"
#include "Score.hpp"
#include "Level.hpp"

using namespace sf;

class Game
{

public:
    void run();
    void mainGameLoop();
    RenderWindow window{VideoMode(570,720),"PacMan"};
    void draw();
    void move();
private:
    void checkIfWindowClosed();
    void reset();
    void hard_reset();
    void checkCollisions();
    void checkGhostCollision(Ghost& ghost);
    void loadCollectives();
    void next_level();
    void freeze(int t);
    void killScreen();
    float dist(float a,float b,float c,float d);
    bool first_freeze=false;

    vector<Bonus> bonuses;
    vector<Point> points;

    Stage stage;
    Player player;
    RedGhost redGhost;
    PinkGhost pinkGhost;
    YellowGhost yellowGhost;
    BlueGhost blueGhost;
    Heart hearts;
    Score score;
    Level level;
};
