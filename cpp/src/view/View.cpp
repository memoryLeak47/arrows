#include "View.hpp"

#include "../misc/Converter.hpp"
#include "../misc/Debug.hpp"
#include "../core/Screen.hpp"

View::View()
	: scale(40), spot(0,0), focusEntity(false)
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

void View::changeFocus()
{
	focusEntity = !focusEntity;
}

void View::setEntity(Entity* e)
{
	entity = e;
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
	return GameVector(getFocus() - screenSize/2);
}

GameVector View::getFocus() const
{
	if (focusEntity)
	{
		return entity->getBody()->getPosition();
	}
	else
	{
		return spot;
	}
}
