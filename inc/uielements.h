#ifndef UI_H
#define UI_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>


class Label
{
private:
    float x, y, size;
    std::string str;
    bool trans;

    sf::RectangleShape rect;
    sf::Font font;
    sf::Text text;

public:
    Label(float px, float py, std::string txt="", float size=64, bool trans=0);
    void draw(sf::RenderWindow& window);
};

class Slider
{
private:
    sf::RectangleShape track;
    sf::CircleShape knob;
    float minValue, maxValue;
    
    float* variableValue;
    bool dragging = 0;

public:
    Slider(float x, float y, float width, float minValue, float maxValue, float* var);

    void handleEvent(sf::Event& event, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
};


class UI
{
private:
    Slider *s1, *s2, *s3;

public:
    UI(float *sep, float *ali, float *coh);
    void draw(sf::RenderWindow& window);
    void handleEvent(sf::Event& event, sf::RenderWindow& window);
};



#endif
