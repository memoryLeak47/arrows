#include "View.hpp"

#include <core/Screen.hpp>
#include <math/pixel/PixelVector.hpp>
#include <math/pixel/PixelRect.hpp>
#include <entity/Entity.hpp>
#include <math/game/GameRect.hpp>

View::View()
	: scale(40), spot(0,0), focusEntity(false)
{}

GameRect View::getVisionRect() const
{
	GameVector screenSize(((float) Screen::getSize().x) / scale, ((float) Screen::getSize().y) / scale);
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
	return PixelRect((int) pos.x, (int) pos.y, (int) size.x, (int) size.y);
}

GameVector View::getGameViewRoot() const
{
	GameVector screenSize(((float) Screen::getSize().x) / scale, ((float) Screen::getSize().y) / scale);
	return GameVector(getFocus() - screenSize/2);
}

GameVector View::getFocus() const
{
	if (focusEntity)
	{
		return entity->getPosition();
	}
	else
	{
		return spot;
	}
}
