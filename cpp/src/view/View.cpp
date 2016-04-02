#include "View.hpp"

#include "../misc/Converter.hpp"
#include "../misc/Debug.hpp"
#include "../core/Screen.hpp"

View::View()
	: scale(40), spot(0,0)
{}

GameRect View::getVisionRect() const
{
	GameVector screenSize(((float) Screen::getSize().getX()) / scale, ((float) Screen::getSize().getY()) / scale);
	return GameRect(getGameViewRoot(), screenSize);
}

void View::updateSpot(const GameVector& s)
{
	spot = s;
}

PixelRect View::gameRectToPixelRect(const GameRect& r) const
{
	GameVector pos = (r.getPosition() - getGameViewRoot()) * scale;
	GameVector size = r.getSize() * scale;
	return PixelRect((int) pos.getX(), (int) pos.getY(), (int) size.getX(), (int) size.getY());
}

GameVector View::getGameViewRoot() const
{
	GameVector screenSize(((float) Screen::getSize().getX()) / scale, ((float) Screen::getSize().getY()) / scale);
	return GameVector(spot - screenSize/2);
}
