#include "View.hpp"

#include "../misc/Debug.hpp"

GameRect View::getVisionRect() const
{
	Debug::warn("View::getVisionRect(): TODO");
	return GameRect(0,0,0,0);
}

void View::updateSpot(const GameVector& s)
{
	spot = s;
}
