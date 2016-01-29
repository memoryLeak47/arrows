#include "PixelVector.h"

PixelVector::PixelVector(float x, float y) : Vector(x, y)
{}

PixelVector::PixelVector(const Vector& v) : Vector(v)
{}

bool PixelVector::inRect(const PixelRect& r) const
{
	return (getX() >= r.getPosition().getX()
	     && getX() <= r.getPosition().getX() - r.getSize().getX()
	     && getY() >= r.getPosition().getY()
	     && getY() <= r.getPosition().getY() - r.getSize().getY());
}

const PixelVector& PixelVector::operator+(const PixelVector& v) const
{
	const PixelVector& pv(Vector::operator+(v));
	return pv;
}

const PixelVector& PixelVector::operator-(const PixelVector& v) const
{
	const PixelVector& pv(Vector::operator-(v));
	return pv;
}
