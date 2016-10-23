#include "PlayerPropertyIcon.hpp"

#include <playerproperty/PlayerProperty.hpp>

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

TextureID PlayerPropertyIcon::getTextureID() const
{
	if (getPlayerProperty() == NULL || getPlayerProperty()->getIconTextureID() == -1)
	{
		return VOID_ICON_GID;
	}
	return getPlayerProperty()->getIconTextureID();
}

PlayerProperty* PlayerPropertyIcon::getPlayerProperty() const
{
	return property;
}
