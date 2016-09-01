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
	return (x >= r.getPosition().x
	     && x <= r.getPosition().x + r.getSize().x
	     && y >= r.getPosition().y
	     && y <= r.getPosition().y + r.getSize().y);
}

bool PixelVector::operator==(const PixelVector& vec) const
{
	return vec.x == x && vec.y == y;
}

bool PixelVector::operator!=(const PixelVector& vec) const
{
	return vec.x != x || vec.y != y;
}

PixelVector PixelVector::operator+(const PixelVector& vec) const
{
	return PixelVector(x + vec.x, y + vec.y);
}

PixelVector PixelVector::operator-(const PixelVector& vec) const
{
	return PixelVector(x - vec.x, y - vec.y);
}

PixelVector PixelVector::operator*(float f) const
{
	return PixelVector(((float) x) * f, ((float) y) * f);
}

PixelVector PixelVector::operator/(float f) const
{
	return PixelVector(((float) x) / f, ((float) y) / f);
}

std::string PixelVector::toString() const
{
	return "(" + Converter::intToString(x) + ", " + Converter::intToString(y) + ")";
}
