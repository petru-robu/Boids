#include <iostream>
#include <SFML/Graphics.hpp>
#include "pvector.h"

#ifndef GAME_H
#define GAME_H

class Game
{
private:
    sf::RenderWindow window;
    int window_height;
    int window_width;

    void HandleInput();
    void Update();
    void Render(); 
    void Init();

public:
    Game();
    void Run();

};




#endif