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
    number_of_boids = 8;
    boid_size = 20;

    for(int i=0; i<number_of_boids; i++)
    {
        sf::CircleShape shape(20, 3);
        shape.setPosition(window_width/2, window_height/2);
        shape.setFillColor(sf::Color::Red);
        shape.setRadius(boid_size);

        bshapes.push_back(shape);
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
        window.draw(bshapes[i]);
    }
    window.display();
}

void Game::Update()
{

}