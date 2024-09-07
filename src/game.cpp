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

    sf::RectangleShape shape;
    shape.setPosition(30, 30);
    shape.setSize(sf::Vector2f(100, 100));
    shape.setFillColor(sf::Color::Red);
   
    window.draw(shape);
    window.display();
}

void Game::Update()
{

}