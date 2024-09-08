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
    number_of_boids = 30;
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
    sf::Vector2i pos = sf::Mouse::getPosition(window);
    pos.x -= window_width/2;
    pos.y -= window_height/2;
    for(int i=0; i<number_of_boids; i++)
    {
        flock[i].seek(Pvector(pos.x, pos.y));
        flock[i].update();

    }
}