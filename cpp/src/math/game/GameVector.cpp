#include "GameVector.hpp"

#include <iostream>
#include <math.h>

#include "../../misc/Converter.hpp"
#include "../../misc/Debug.hpp"

GameVector::GameVector(float x, float y)
{
	this->x = x;
	this->y = y;
}

bool GameVector::inRect(const GameRect& r) const
{
	return (x >= r.getPosition().x
	     && x <= r.getPosition().x + r.getSize().x
	     && x >= r.getPosition().y
	     && x <= r.getPosition().y + r.getSize().y);
}

float GameVector::getMagnitude() const
{
	return sqrt(x * x + y * y);
}

void GameVector::setMagnitude(float mag)
{
	GameVector v = getNormalized() * mag;
	x = v.x;
	y = v.y;
}

GameVector GameVector::withMagnitude(float mag) const
{
	return getNormalized() * mag;
}

GameVector GameVector::getNormalized() const
{
	if (getMagnitude() == 0) Debug::warn("GameVector::getNormalized(): division by zero");
	return *this/getMagnitude();
}

GameVector GameVector::getProjectionOn(const GameVector& arg) const
{
	GameVector tmp = arg.getNormalized();
	return tmp * getScalarProduct(*this, tmp);
}

GameVector GameVector::getOrthogonal() const
{
	return GameVector(-y, x);
}

float GameVector::getScalarProduct(const GameVector& vec1, const GameVector& vec2)
{
	return vec1.x * vec2.x + vec1.y * vec2.y;
}

bool GameVector::operator==(const GameVector& vec) const
{
	return vec.x == x && vec.y == y;
}

bool GameVector::operator!=(const GameVector& vec) const
{
	return vec.x != x || vec.y != y;
}

GameVector GameVector::operator+=(const GameVector& vec)
{
	x += vec.x;
	y += vec.y;
	return *this;
}

GameVector GameVector::operator-=(const GameVector& vec)
{
	x -= vec.x;
	y -= vec.y;
	return *this;
}

GameVector GameVector::operator+(const GameVector& vec) const
{
	return GameVector(x + vec.x, y + vec.y);
}

GameVector GameVector::operator-(const GameVector& vec) const
{
	return GameVector(x - vec.x, y - vec.y);
}

GameVector GameVector::operator-() const
{
	return GameVector(-x, -y);
}

GameVector GameVector::operator*(float f) const
{
	return GameVector(x*f, y*f);
}

GameVector GameVector::operator/(float f) const
{
	return GameVector(x/f, y/f);
}

std::string GameVector::toString() const
{
	return "(" + Converter::floatToString(x) + ", " + Converter::floatToString(y) + ")";
}
