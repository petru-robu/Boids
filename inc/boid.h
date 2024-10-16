#include <iostream>
#include <SFML/Graphics.hpp>
#include "pvector.h"
#include "utility.h"

#ifndef BOID_H
#define BOID_H

class Boid
{
public:

    Pvector location;
    Pvector velocity;
    Pvector acceleration;

    float maxSpeed;
    float maxForce;

    float separationFactor;
    float alignmentFactor;
    float cohesionFactor;

    int boidSize;
    sf::CircleShape boid_shape;

    Boid();
    Boid(float x, float y);

    void setPosition(float x, float y);
    void setVelocity(float x, float y);
    void setAcceleration(float x, float y);

    sf::CircleShape getDrawable();

    void applyForce(const Pvector& force);
    Pvector seek(const Pvector& target);
    Pvector chase(const Pvector& vec);
    
    Pvector separation(const std::vector<Boid> &flock);
    Pvector cohesion(const std::vector<Boid> &flock);
    Pvector alignment(const std::vector<Boid> &flock);

    void flocking(const std::vector<Boid> &flock);

    void draw(sf::RenderWindow &window);
    void wrap();
    void update();
    void run(const std::vector<Boid> &flock);
    
};




#endif