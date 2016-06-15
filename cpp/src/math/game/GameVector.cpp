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
	return (getX() >= r.getPosition().getX()
	     && getX() <= r.getPosition().getX() + r.getSize().getX()
	     && getY() >= r.getPosition().getY()
	     && getY() <= r.getPosition().getY() + r.getSize().getY());
}

float GameVector::getX() const { return x; }
float GameVector::getY() const { return y; }

void GameVector::apply(const GameVector& g)
{
	x = g.getX();
	y = g.getY();
}

float GameVector::getMagnitude() const
{
	return sqrt(getX() * getX() + getY() * getY());
}

float GameVector::getScalarProduct(const GameVector& vec1, const GameVector& vec2)
{
	return vec1.getX() * vec2.getX() + vec1.getY() * vec2.getY();
}

bool GameVector::operator==(const GameVector& vec) const
{
	return vec.getX() == getX() && vec.getY() == getY();
}

bool GameVector::operator!=(const GameVector& vec) const
{
	return vec.getX() != getX() || vec.getY() != getY();
}

GameVector GameVector::operator+(const GameVector& vec) const
{
	float x = getX() + vec.getX();
	float y = getY() + vec.getY();
	return GameVector(x, y);
}

GameVector GameVector::operator-(const GameVector& vec) const
{
	float x = getX() - vec.getX();
	float y = getY() - vec.getY();
	return GameVector(x, y);
}

GameVector GameVector::operator*(float f) const
{
	return GameVector(getX()*f, getY()*f);
}

GameVector GameVector::operator/(float f) const
{
	return GameVector(getX()/f, getY()/f);
}

std::string GameVector::toString() const
{
	return "GV(" + Converter::floatToString(getX()) + ", " + Converter::floatToString(getY()) + ")";
}
