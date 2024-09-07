#include <iostream>
#include <SFML/Graphics.hpp>
#include "pvector.h"

#ifndef BOID_H
#define BOID_H

class Boid
{
public:

Pvector location, velocity, acceleration;
float maxSpeed, maxForce;

Boid(){};

};




#endif