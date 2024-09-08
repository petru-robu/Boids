#include "../inc/pvector.h"

Pvector::Pvector(){}
Pvector::Pvector(float x, float y): x(x), y(y) {}
Pvector::Pvector(sf::Vector2f vec): x(vec.x), y(vec.y) {}

void Pvector::set(float x, float y)
{
    this->x = x;
    this->y = y;
}

void Pvector::set(sf::Vector2f vec)
{
    x = vec.x;
    y = vec.y;
}

Pvector Pvector::operator+(Pvector const& vec)
{
    Pvector ans;
    ans.x = x + vec.x;
    ans.y = y + vec.y;

    return ans;
}
Pvector Pvector::operator+(float scalar)
{
    Pvector ans;
    ans.x = x + scalar;
    ans.y = y + scalar;

    return ans;
}

Pvector Pvector::operator-(Pvector const& vec)
{
    Pvector ans;
    ans.x = x - vec.x;
    ans.y = y - vec.y;

    return ans;
}
Pvector Pvector::operator-(float scalar)
{
    Pvector ans;
    ans.x = x - scalar;
    ans.y = y - scalar;

    return ans;
}

Pvector Pvector::operator*(Pvector const& vec)
{
    Pvector ans;
    ans.x = x * vec.x;
    ans.y = y * vec.y;

    return ans;
}
Pvector Pvector::operator*(float scalar)
{
    Pvector ans;
    ans.x = x * scalar;
    ans.y = y * scalar;

    return ans;
}

Pvector Pvector::operator/(Pvector const& vec)
{
    Pvector ans;
    ans.x = x / vec.x;
    ans.y = y / vec.y;

    return ans;
}
Pvector Pvector::operator/(float scalar)
{
    Pvector ans;
    ans.x = x / scalar;
    ans.y = y / scalar;

    return ans;
}

Pvector& Pvector::operator+=(Pvector const& vec)
{
    x += vec.x;
    y += vec.y;

    return *this;
}
Pvector& Pvector::operator+=(float scalar)
{
    x += scalar;
    y += scalar;

    return *this;
}

Pvector& Pvector::operator-=(Pvector const& vec)
{
    x -= vec.x;
    y -= vec.y;

    return *this;
}
Pvector& Pvector::operator-=(float scalar)
{
    x -= scalar;
    y -= scalar;

    return *this;
}

Pvector& Pvector::operator*=(Pvector const& vec)
{
    x *= vec.x;
    y *= vec.y;

    return *this;
}
Pvector& Pvector::operator*=(float scalar)
{
    x *= scalar;
    y *= scalar;

    return *this;
}

Pvector& Pvector::operator/=(Pvector const& vec)
{
    x /= vec.x;
    y /= vec.y;

    return *this;
}
Pvector& Pvector::operator/=(float scalar)
{
    x /= scalar;
    y /= scalar;

    return *this;
}

float Pvector::magnitude()
{
    return sqrt(x*x + y*y);
}

void Pvector::normalize()
{
    float m = magnitude();
    if(m > 0)
        *this = *this / m;
}

void Pvector::setMagnitude(float m)
{
    normalize();
    *this = *this * m;
}

float Pvector::dotProduct(const Pvector& vec)
{
    float dot = x * vec.x + y * vec.y;
    return dot;
}

float Pvector::angleBetween(const Pvector& vec)
{
    if (x == 0 && y == 0) return 0.0f;
    if (vec.x == 0 && vec.y == 0) return 0.0f;

    float dot = x*vec.x + y*vec.y;
    float v1mag = sqrt(x*x + y*y);
    float v2mag = sqrt(vec.x*vec.x + vec.y*vec.y);

    float ang = dot / (v1mag * v2mag);

    if(ang <= -1)
        return PI;
    else if(ang >= 1)
        return 0;
    
    float tmp = acos(ang);
    return tmp;
}

void Pvector::limit(float maxsp)
{
    float m = magnitude();
    if(m > maxsp)
        set(x/m, y/m);
}