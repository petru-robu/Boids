#include "../inc/game.h"

#include <memory>

Game::Game()
{
    window_width = 1000;
    window_height = 800;
    window.create(sf::VideoMode({static_cast<unsigned int>(window_width), static_cast<unsigned int>(window_height)}), "Window");
    window.setFramerateLimit(60);

    separationFactor = 2;
    alignmentFactor = 1.5;
    cohesionFactor = 1.5;

    ui = std::make_unique<UI>(&separationFactor, &alignmentFactor, &cohesionFactor);
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
    number_of_boids = 300;
    for(int i=0; i<number_of_boids; i++)
    {
        int rx = range_random(10, window_width - 10);
        int ry = range_random(10, window_height - 10);

        flock.emplace_back(rx, ry, &separationFactor, &alignmentFactor, &cohesionFactor);

    }
}

void Game::HandleInput()
{
    while (const auto event = window.pollEvent()) 
    {
        if(event->is<sf::Event::Closed>())
            window.close();

        if(const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
        {
            if(keyPressed->code == sf::Keyboard::Key::Escape)
                window.close();
            if(keyPressed->code == sf::Keyboard::Key::Backspace)
                window.close();
            if(keyPressed->code == sf::Keyboard::Key::X)
                window.close();           
        }

        ui->handleEvent(*event, window);
    }
}

void Game::Render()
{
    window.clear();

    for(int i=0; i<number_of_boids; i++)
        flock[i].draw(window);

    ui->draw(window);
    
    window.display();
}

void Game::Update()
{
    for(int i=0; i<number_of_boids; i++)
        flock[i].run(flock);
}
