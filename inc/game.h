#include <iostream>
#include <SFML/Graphics.hpp>
#include "pvector.h"
#include "utility.h"
#include "boid.h"

#ifndef GAME_H
#define GAME_H

class Game
{
private:
    sf::RenderWindow window;
    int window_height;
    int window_width;

    int number_of_boids;
    
    std::vector<Boid> flock;

    void HandleInput();
    void Update();
    void Render(); 
    void Init();

public:
    Game();
    void Run();

};




#endif