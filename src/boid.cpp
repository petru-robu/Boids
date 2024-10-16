#include "../inc/boid.h"

#define sim_width 1000
#define sim_height 800

Boid::Boid(float x, float y, float* separationFactor, float* alignmentFactor, float* cohesionFactor): 
separationFactor(separationFactor), alignmentFactor(alignmentFactor), cohesionFactor(cohesionFactor)
{
    maxSpeed = 3;
    maxForce = 0.05;

    boidSize = 5;

    acceleration = Pvector(0, 0);
    location = Pvector(0, 0);
    velocity = Pvector(rand()%3-2, rand()%3-2);
    
    boid_shape = sf::CircleShape(20, 3);
    boid_shape.setFillColor(sf::Color::Red);
    boid_shape.setRadius(boidSize);
    boid_shape.setOrigin(10, 0);

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

void Boid::wrap()
{
    if (location.x < 0)    
        location.x += sim_width;
    
    if (location.y < 0)    
        location.y += sim_height;
    
    if (location.x >= sim_width)
        location.x -= sim_width;
    
    if (location.y >= sim_height) 
        location.y -= sim_height;
}

void Boid::update()
{
    velocity += acceleration;
    velocity = velocity.limited(maxSpeed);

    location += velocity;

    acceleration *= 0;   

    float angle = (float)(atan2(velocity.x, -velocity.y) * 180 / PI);
    boid_shape.setRotation(angle);
}

void Boid::draw(sf::RenderWindow &window)
{
    boid_shape.setPosition(sf::Vector2f(location.x, location.y));
    window.draw(boid_shape);
}

sf::CircleShape Boid::getDrawable()
{
    return boid_shape;
}

Pvector Boid::separation(const std::vector<Boid> &flock, float fov)
{
    float cnt = 0;
    Pvector steer(0, 0);

    for(int i=0; i<flock.size(); i++)
    {
        float d = location.distance(flock[i].location);
        
        if(d > 0 && d < fov)
        {
            Pvector dir;
            dir = location - flock[i].location;
            
            dir = dir.normalized();
            steer = steer + dir / d;

            cnt++;
        }
    }

    if(cnt > 0)
        steer/= cnt;

    if(steer.magnitude() > 0)
    {
        steer = steer.normalized();
        steer *= maxSpeed;
        steer -= velocity;
        steer = steer.limited(maxForce);
    }

    return steer;
}

Pvector Boid::alignment(const std::vector<Boid> &flock, float fov)
{
    float cnt = 0;
    Pvector avg(0, 0);

    for(int i=0; i<flock.size(); i++)
    {
        float d = location.distance(flock[i].location);
        
        if(d > 0 && d < fov)
        {
            avg += flock[i].velocity;
            cnt++;
        }
    }

    if(cnt > 0)
    {
        avg /= cnt;
        avg = avg.normalized();
        avg *= maxSpeed;

        Pvector dir;
        dir = avg - velocity;
        dir = dir.limited(maxForce);
        return dir;
    }

    return Pvector(0,0);

}

Pvector Boid::cohesion(const std::vector<Boid> &flock, float fov)
{
    float cnt = 0;
    Pvector avg(0, 0);

    for(int i=0; i<flock.size(); i++)
    {
        float d = location.distance(flock[i].location);
        
        if(d > 0 && d < fov)
        {
            avg += flock[i].location;
            cnt++;
        }
    }

    if(cnt > 0)
    {
        avg /= cnt;

        Pvector dir;
        dir = avg - location;
        dir = dir.normalized();
        dir*=maxSpeed;

        Pvector steer;
        steer = dir - velocity;
        steer = steer.limited(maxForce);
        return steer;
    }
    return Pvector(0, 0);
}

void Boid::flocking(const std::vector<Boid> &flock)
{
    float fov_sep = 20;
    float fov_alg = 60;
    float fov_coh = 60;

    Pvector sep = separation(flock,fov_sep);
    Pvector alg = alignment(flock, fov_alg);
    Pvector coh = cohesion(flock, fov_coh);

    sep*=(*separationFactor);
    alg*=(*alignmentFactor);
    coh*=(*cohesionFactor);
    
    applyForce(sep);
    applyForce(alg);
    applyForce(coh);
}

void Boid::run(const std::vector<Boid> &flock)
{
    flocking(flock);
    wrap(); 
    update();
}
