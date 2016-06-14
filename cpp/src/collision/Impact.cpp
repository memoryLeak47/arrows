#include "Impact.hpp"

Impact::Impact(const GameVector& a, float b, const GameVector& c)
	: speed(a), strength(b), impactPoint(c)
{}

const GameVector& Impact::getSpeed() const
{
	return speed;
}

float Impact::getStrength() const
{
	return strength;
}

const GameVector& Impact::getImpactPoint() const
{
	return impactPoint;
}
