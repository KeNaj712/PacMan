#include "Game.hpp"

void Game::run()
{
    window.setFramerateLimit(60);
    loadCollectives();
    mainGameLoop();
}

void Game::mainGameLoop()
{
    while (window.isOpen())
    {
        checkIfWindowClosed();
        if(!first_freeze)
        {
            freeze(90);
            first_freeze=true;
        }
        move();
        checkCollisions();
        if(bonuses.empty() && points.empty())
            next_level();
        draw();
        window.display();
    }
}

void Game::checkIfWindowClosed()
{
    Event event;
    while (window.pollEvent(event))
    {
        if (event.type == Event::Closed)
        {
            window.close();
            exit(0);
        }

    }
}

void Game::move()
{
    player.move(stage);
    redGhost.move(stage,player);
    pinkGhost.move(stage,player);
    yellowGhost.move(stage,player);
    blueGhost.update_red_coords(redGhost);
    blueGhost.move(stage,player);
}

void Game::draw()
{
    window.clear(Color::Black);
    stage.draw(window);

    for(Bonus& x:bonuses)
        x.draw(window);
    for(Point& x:points)
        x.draw(window);

    redGhost.draw(window);
    pinkGhost.draw(window);
    yellowGhost.draw(window);
    blueGhost.draw(window);

    player.draw(window);
    hearts.draw(window);
    score.draw(window);
    level.draw(window);
}

void Game::loadCollectives()
{
    float a,b;

    ifstream infile("txt_files/bonuses.txt");
    while(infile>>a>>b)
        bonuses.push_back(Bonus(a,b));

    ifstream infile2("txt_files/points.txt");
    while(infile2>>a>>b)
        points.push_back(Point(a,b));
}

void Game::checkCollisions()
{
    for(int x=0;x<(int)bonuses.size();x++)
    {
        if(dist(player.coord_x,player.coord_y,bonuses[x].coord_x,bonuses[x].coord_y)<40)
        {
            score.update(50);
            bonuses.erase(bonuses.begin()+x);
            redGhost.trigger_scared();
            pinkGhost.trigger_scared();
            blueGhost.trigger_scared();
            yellowGhost.trigger_scared();
            break;
        }
    }

    for(int x=0;x<(int)points.size();x++)
    {
        if(dist(player.coord_x,player.coord_y,points[x].coord_x,points[x].coord_y)<20)
        {
            score.update(10);
            points.erase(points.begin()+x);
            break;
        }
    }

    checkGhostCollision(redGhost);
    checkGhostCollision(blueGhost);
    checkGhostCollision(yellowGhost);
    checkGhostCollision(pinkGhost);
}

void Game::checkGhostCollision(Ghost& ghost)
{
    if(dist(player.coord_x,player.coord_y,ghost.coord_x,ghost.coord_y)<300)
    {
        if(ghost.mode==0 || ghost.mode==1)
        {
            freeze(60);
            player.killed=true;
            freeze(135);
            reset();
            hearts.cnt--;
            if(hearts.cnt==0)
                killScreen();

        }
        else if(ghost.mode==2)
        {
            ghost.trigger_killed();
            score.update(200);
        }

    }
}

float Game::dist(float a,float b,float c,float d)
{
    return (a-c)*(a-c)+(b-d)*(b-d);
}

void Game::freeze(int t)
{
    player.timer=-t;
    for(auto& x:bonuses)
        x.timer=-t;
    while(t--)
    {
        checkIfWindowClosed();
        draw();
        window.display();
    }
}

void Game::reset()
{
    player.reset();
    redGhost.reset();
    blueGhost.reset();
    yellowGhost.reset();
    pinkGhost.reset();
    first_freeze=false;
}

void Game::hard_reset()
{
    reset();
    score.reset();
    level.reset();
    hearts.reset();
    bonuses.clear();
    points.clear();
    loadCollectives();
}

void Game::next_level()
{
    freeze(90);
    loadCollectives();
    reset();
    level.next();
}

void Game::killScreen()
{
    Font font;
    font.loadFromFile("fonts/joystix_monospace.ttf");
    Text text1("GAME OVER",font);
    Text text2("Your score: " + score.get_score(),font);
    Text text3("Press R to restart",font);
    text1.setCharacterSize(70);
    text2.setCharacterSize(30);
    text3.setCharacterSize(20);
    text1.setPosition(23,50);
    text2.setPosition(50,350);
    text3.setPosition(135,600);
    int timer_killScreen=0;
    while (window.isOpen())
    {
        checkIfWindowClosed();
        window.clear(Color::Black);
        if(timer_killScreen>60)
            window.draw(text1);
        if(timer_killScreen>120)
            window.draw(text2);
        if(timer_killScreen>240 && timer_killScreen%40<20)
            window.draw(text3);
        if(timer_killScreen>240 && Keyboard::isKeyPressed(Keyboard::R))
        {
            hard_reset();
            break;
        }
        window.display();
        timer_killScreen++;
    }
}
