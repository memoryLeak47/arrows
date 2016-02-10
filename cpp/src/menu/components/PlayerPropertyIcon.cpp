#include "PlayerPropertyIcon.hpp"

extern int VOID_ICON;

PlayerPropertyIcon::PlayerPropertyIcon(ComponentContainer* c, const PixelRect& r, PlayerProperty* p)
	: Icon(c, r)
{
	setPlayerProperty(p);
}

PixelVector PlayerPropertyIcon::getSize()
{
	return PixelVector(40, 40);
}

void PlayerPropertyIcon::setPlayerProperty(PlayerProperty* prop)
{
	property = prop;
}

TextureID PlayerPropertyIcon::getTextureID() const
{
	if (getPlayerProperty() == NULL)
	{
		return VOID_ICON;
	}
	return getPlayerProperty()->getIconTextureID();
}

PlayerProperty* PlayerPropertyIcon::getPlayerProperty() const
{
	return property;
}
