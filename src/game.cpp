#include "../inc/game.h"

Game::Game()
{
    window_width = 1000;
    window_height = 800;
    window.create(sf::VideoMode(window_width, window_height), "Window");
    window.setFramerateLimit(60);
}

void Game::Run()
{
    Init();

    while(window.isOpen())
    {
        HandleInput();
        Update();
        Render();
    }
}

void Game::Init()
{
    number_of_boids = 50;
    for(int i=0; i<number_of_boids; i++)
    {
        int rx = range_random(10, window_width - 10);
        int ry = range_random(10, window_height - 10);

        Boid new_boid(rx, ry);
        flock.push_back(new_boid);

    }
}

void Game::HandleInput()
{
    sf::Event event;
    while (window.pollEvent(event)) 
    {
        if(event.type == sf::Event::Closed)
            window.close();
        if(event.type == sf::Event::KeyPressed)
        {
            if(event.key.code == sf::Keyboard::Escape)
                window.close();
            if(event.key.code == sf::Keyboard::BackSpace)
                window.close();
            if(event.key.code == sf::Keyboard::X)
                window.close();           
        }
    }
}

void Game::Render()
{
    window.clear();

    for(int i=0; i<number_of_boids; i++)
    {
        window.draw(flock[i].getDrawable());
    }
    window.display();
}

void Game::Update()
{
    sf::Vector2i pos;
    pos = sf::Mouse::getPosition(window);

    int flag;

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        flag = 1;
    else
        flag = -1;

    for(int i=0; i<number_of_boids; i++)
    {
        if(flag == 1)
        {
            Pvector mp(pos.x, pos.y);
            mp.normalize();
            float factor = 5;
            mp *= factor;

            flock[i].velocity += mp;
        }
            
            
        flock[i].run(flock);
    }
        
}