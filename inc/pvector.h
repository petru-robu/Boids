#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <math.h>
#define PI 3.14159

class Pvector
{
public:
    float x, y;

    Pvector();
    Pvector(float x, float y);
    Pvector(sf::Vector2f vec);

    void set(float x, float y);
    void set(sf::Vector2f vec);

    Pvector operator+(const Pvector& vec);
    Pvector operator+(float scalar);

    Pvector operator-(const Pvector&  vec);
    Pvector operator-(float scalar);

    Pvector operator*(const Pvector& vec);
    Pvector operator*(float scalar);

    Pvector operator/(const Pvector& vec);
    Pvector operator/(float scalar);

    Pvector& operator+=(const Pvector& vec);
    Pvector& operator+=(float scalar);

    Pvector& operator-=(const Pvector& vec);
    Pvector& operator-=(float scalar);

    Pvector& operator*=(const Pvector& vec);
    Pvector& operator*=(float scalar);

    Pvector& operator/=(const Pvector& vec);
    Pvector& operator/=(float scalar);

    Pvector& operator=(const Pvector& vec);

    Pvector normalized();
    Pvector limited(float maxsp);
    
    float magnitude();
    float dotProduct(const Pvector& vec);
    float angleBetween(const Pvector& vec);
    float distance(const Pvector& vec);

};


#endif