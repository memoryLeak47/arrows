#include "CollisionLine.hpp"

CollisionLine::CollisionLine(const GameVector& arg1, const GameVector& arg2)
	: point1(arg1), point2(arg2)
{}

bool CollisionLine::isValid() const
{
	return (point1 != GameVector(-1, -1)) && (point2 != GameVector(-1, -1));
}
