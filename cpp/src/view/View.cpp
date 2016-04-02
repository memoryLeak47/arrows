#include "View.hpp"

#include "../misc/Debug.hpp"

View::View()
	: spot(0,0)
{}

GameRect View::getVisionRect() const
{
	Debug::warn("View::getVisionRect(): TODO");
	return GameRect(0,0,0,0);
}

void View::updateSpot(const GameVector& s)
{
	spot = s;
}

PixelRect View::gameRectToPixelRect(const GameRect&) const
{
	Debug::warn("View::gameRectToPixelRect(): TODO");
	return PixelRect(0, 0, 1, 1);
}
