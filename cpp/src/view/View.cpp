#include "View.hpp"

#include <core/Screen.hpp>
#include <math/pixel/PixelVector.hpp>
#include <math/pixel/PixelRect.hpp>
#include <math/game/GameRect.hpp>

View::View()
	: scale(40), spot(0,0)
{}

GameRect View::getVisionRect() const
{
	GameVector screenSize(((float) Screen::getSize().x) / scale, ((float) Screen::getSize().y) / scale);
	return GameRect(getGameViewRoot(), screenSize);
}

void View::setSpot(const GameVector& s)
{
	spot = s;
}

PixelRect View::gameRectToPixelRect(const GameRect& r) const
{
	GameVector pos = (r.getPosition() - getGameViewRoot()) * scale;
	GameVector size = r.getSize() * scale;
	return PixelRect((int) pos.x, (int) pos.y, (int) size.x, (int) size.y);
}

GameVector View::getGameViewRoot() const
{
	GameVector screenSize(((float) Screen::getSize().x) / scale, ((float) Screen::getSize().y) / scale);
	return GameVector(getSpot() - screenSize/2);
}

GameVector View::getSpot() const
{
	return spot;
}
