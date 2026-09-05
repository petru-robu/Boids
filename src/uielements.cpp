#include "../inc/uielements.h"

#include <memory>

//Label
Label::Label(float x, float y, std::string s, float size, bool trans):
    x(x), y(y), size(size), str(s), trans(trans), text(font, s, static_cast<unsigned int>(size))
{
    if(!font.openFromFile("./res/arial.ttf"))
    {
        std::cout<<"Missing font!\n";
    }

    text.setFillColor(sf::Color::White);
    text.setPosition({x+size/4, y});

    if(!trans)
    {
        sf::FloatRect fr = text.getLocalBounds();
        rect.setPosition({x, y});
        rect.setSize({fr.size.x+size/2, fr.size.y+size/2});
        rect.setFillColor(sf::Color::Blue);
    }
}

void Label::draw(sf::RenderWindow& window)
{
    window.draw(rect);
    window.draw(text);
}


//Slider
Slider::Slider(float x, float y, float width, float minValue, float maxValue, float* var):
    minValue(minValue), maxValue(maxValue), variableValue(var)
    {
        track.setPosition({x, y});
        track.setSize({width, 3});
        track.setFillColor(sf::Color::White);

        knob.setRadius(6);
        knob.setFillColor(sf::Color::White);
        knob.setPosition({x, y-5});
    }

void Slider::handleEvent(const sf::Event& event, sf::RenderWindow& window)
{
    if(const auto* mouseButtonPressed = event.getIf<sf::Event::MouseButtonPressed>())
    {
        if(mouseButtonPressed->button == sf::Mouse::Button::Left)
        {
            sf::Vector2f mousePos = window.mapPixelToCoords(mouseButtonPressed->position);
            if(knob.getGlobalBounds().contains(mousePos))
            {
                dragging = 1;
                //std::cout<<"DRAG\n";
            }
        }
        
    }

    if(const auto* mouseButtonReleased = event.getIf<sf::Event::MouseButtonReleased>())
    {
        if(mouseButtonReleased->button == sf::Mouse::Button::Left)
            dragging = 0;
    }

    if(const auto* mouseMoved = event.getIf<sf::Event::MouseMoved>(); mouseMoved && dragging)
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            sf::Vector2f mousePos = window.mapPixelToCoords(mouseMoved->position);
            float newX = std::clamp(mousePos.x, track.getPosition().x, 
                                    track.getPosition().x + track.getSize().x);

            knob.setPosition({newX, knob.getPosition().y});
            float ratio = (newX - track.getPosition().x) / track.getSize().x;
            *variableValue = minValue + ratio * (maxValue - minValue);
        }
    }
}

void Slider::draw(sf::RenderWindow& window)
{
    window.draw(track);
    window.draw(knob);
}

//UI
UI::UI(float *sep, float *ali, float *coh)
{
    s1 = std::make_unique<Slider>(95, 15, 150, 0, 3.5, sep);
    s2 = std::make_unique<Slider>(95, 40, 150, 0, 3.5, ali);
    s3 = std::make_unique<Slider>(95, 65, 150, 0, 3.5, coh);
}

void UI::handleEvent(const sf::Event& event, sf::RenderWindow& window)
{
    s1->handleEvent(event, window);
    s2->handleEvent(event, window);
    s3->handleEvent(event, window);
}

void UI::draw(sf::RenderWindow& window)
{
    Label l1(5, 5, "Separation: ", 15, 1);
    Label l2(5, 30, "Alignment: ", 15, 1);
    Label l3(5, 55, "Cohesion: ", 15, 1);

    Label credits(820, 780, "Made by Petru 16.10.2024", 15, 1);
    Label title(0, 780, "Boids: Flocking Simulator in C++", 15, 1);


    credits.draw(window);
    title.draw(window);

    s1->draw(window);
    s2->draw(window);
    s3->draw(window);

    l1.draw(window);
    l2.draw(window);
    l3.draw(window);
}
