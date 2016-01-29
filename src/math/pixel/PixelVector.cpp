#include "PixelVector.h"

#include <iostream>

PixelVector::PixelVector(float x, float y)
{
	this->x = x;
	this->y = y;
}

bool PixelVector::inRect(const PixelRect& r) const
{
	return (getX() >= r.getPosition().getX()
	     && getX() <= r.getPosition().getX() + r.getSize().getX()
	     && getY() >= r.getPosition().getY()
	     && getY() <= r.getPosition().getY() + r.getSize().getY());
}

int PixelVector::getX() const { return x; }
int PixelVector::getY() const { return y; }

bool PixelVector::operator==(const PixelVector& vec) const
{
	return vec.getX() == getX() && vec.getY() == getY();
}

bool PixelVector::operator!=(const PixelVector& vec) const
{
	return vec.getX() != getX() || vec.getY() != getY();
}

const PixelVector& PixelVector::operator+(const PixelVector& vec) const
{
	float x = getX() + vec.getX();
	float y = getY() + vec.getY();
	const PixelVector& v = PixelVector(x, y);
	return v;
}

const PixelVector& PixelVector::operator-(const PixelVector& vec) const
{
	float x = getX() - vec.getX();
	float y = getY() - vec.getY();
	const PixelVector& v = PixelVector(x, y);
	return v;
}
