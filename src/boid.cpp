#include "../inc/boid.h"

#define width 1000
#define height 800

Boid::Boid()
{
    maxSpeed = 3;
    maxForce = 1.5;
    boidSize = 10;

    acceleration = Pvector(0, 0);
    location = Pvector(0, 0);
    velocity = Pvector(rand()%3-2, rand()%3-2);
    //velocity = Pvector(0, 0);

    
    boid_shape = sf::CircleShape(20, 3);
    boid_shape.setFillColor(sf::Color::Red);
    boid_shape.setRadius(boidSize);
}

Boid::Boid(float x, float y) : Boid()
{
    location.x = x;
    location.y = y;
}

void Boid::setPosition(float x, float y)
{
    location.x = x;
    location.y = y;
}
void Boid::setVelocity(float x, float y)
{
    velocity.x = x;
    velocity.y = y;
}
void Boid::setAcceleration(float x, float y)
{
    acceleration.x = x;
    acceleration.y = y;
}


void Boid::applyForce(const Pvector& force)
{
    acceleration += force;
}

void Boid::seek(const Pvector& target)
{
    Pvector desired = target;
    //desired *= -1;
    desired.normalize();
    desired *= maxSpeed;

    acceleration = desired - velocity;
    acceleration.limit(maxForce);
}

void Boid::update()
{
    acceleration *= 0.5;

    velocity += acceleration;
    velocity.limit(maxSpeed);

    location += velocity;

    acceleration *= 0;

    if (location.x < 0)    
        location.x += 1000;
    
    if (location.y < 0)    
        location.y += 800;
    
    if (location.x > 1000)
        location.x -= 1000;
    
    if (location.y > 800) 
        location.y -= 800;

    float angle = (float)(atan2(velocity.x, -velocity.y) * 180 / PI);
    boid_shape.setRotation(angle);

    boid_shape.setPosition(sf::Vector2f(location.x, location.y));
}

sf::CircleShape Boid::getDrawable()
{
    return boid_shape;
}