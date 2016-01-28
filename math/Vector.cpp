#include "Vector.h"

Vector::Vector(float x, float y)
{
	this->x = x;
	this->y = y;
}

Vector::Vector(const Vector& vec) : x(vec.getX()), y(vec.getY())
{}

float Vector::getX() const { return x; }
float Vector::getY() const { return y; }
