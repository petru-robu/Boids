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
    number_of_boids = 150;
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
            
            if(event.key.code == sf::Keyboard::W)
            {
                flock[0].applyForce(Pvector(1, 0));
            }
        }
    }
}

void Game::Render()
{
    window.clear();

    for(int i=0; i<number_of_boids; i++)
        flock[i].draw(window);
    
    window.display();
}

void Game::Update()
{
    sf::Vector2i pos;
    pos = sf::Mouse::getPosition(window);

    int cnt = 0;
    for(int i=0; i<number_of_boids; i++)
    {              
        flock[i].run(flock);
        if(flock[i].location.x >= 0 && flock[i].location.x <= 1000 && flock[i].location.y >= 0  && flock[i].location.x <= 800)
            cnt++;
    }
    std::cout<<cnt<<" Boids on screen!\n";
}