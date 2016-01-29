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

bool Vector::operator==(const Vector& vec) const
{
	return vec.getX() == getX() && vec.getY() == getY();
}

bool Vector::operator!=(const Vector& vec) const
{
	return !(vec.getX() == getX() && vec.getY() == getY());
}

const Vector& Vector::operator+(const Vector& vec) const
{
	float x = getX() + vec.getX();
	float y = getY() + vec.getY();
	const Vector& v = Vector(x, y);
	return v;
}

const Vector& Vector::operator-(const Vector& vec) const
{
	float x = getX() - vec.getX();
	float y = getY() - vec.getY();
	const Vector& v = Vector(x, y);
	return v;
}
