#include "PlayerPropertyIcon.hpp"

PlayerPropertyIcon::PlayerPropertyIcon(ComponentContainer* c, const PixelRect& r, PlayerProperty* p)
	: Icon(c, r)
{
	setPlayerProperty(p);
}

PlayerPropertyIcon::PlayerPropertyIcon(ComponentContainer* c, const PixelRect& r)
	: Icon(c, r)
{
	setPlayerProperty(NULL);
}

PixelVector PlayerPropertyIcon::getSize()
{
	return PixelVector(40, 40);
}

void PlayerPropertyIcon::setPlayerProperty(PlayerProperty* prop)
{
	property = prop;
}

GraphicsID PlayerPropertyIcon::getGraphicsID() const
{
	if (getPlayerProperty() == NULL || getPlayerProperty()->getIconGraphicsID() == -1)
	{
		return VOID_ICON_GID;
	}
	return getPlayerProperty()->getIconGraphicsID();
}

PlayerProperty* PlayerPropertyIcon::getPlayerProperty() const
{
	return property;
}
