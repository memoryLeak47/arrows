#include "PixelVector.hpp"

#include "../../misc/Debug.hpp"
#include "../../misc/Converter.hpp"

PixelVector::PixelVector(int x, int y)
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

PixelVector PixelVector::operator+(const PixelVector& vec) const
{
	int x = getX() + vec.getX();
	int y = getY() + vec.getY();
	return PixelVector(x, y);
}

PixelVector PixelVector::operator-(const PixelVector& vec) const
{
	int x = getX() - vec.getX();
	int y = getY() - vec.getY();
	return PixelVector(x, y);
}

PixelVector PixelVector::operator*(float f) const
{
	return PixelVector(((float)getX())*x, ((float)getY())*y);
}

PixelVector PixelVector::operator/(float f) const
{
	return PixelVector(((float) getX())/f, ((float) getY())/f);
}

std::string PixelVector::toString() const
{
	return "PV(" + Converter::intToString(getX()) + ", " + Converter::intToString(getY()) + ")";
}
