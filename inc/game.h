#include <iostream>
#include <SFML/Graphics.hpp>
#include "pvector.h"
#include "utility.h"
#include "boid.h"
#include "uielements.h"

#ifndef GAME_H
#define GAME_H

class Game
{
private:
    sf::RenderWindow window;
    int window_height;
    int window_width;

    UI *ui;

    int number_of_boids;
    std::vector<Boid> flock;
    float separationFactor;
    float alignmentFactor;
    float cohesionFactor;

    void HandleInput();
    void Update();
    void Render(); 
    void Init();

public:
    Game();
    void Run();

};


#endif