#include "MiniMap.hpp"

extern int VOID_ICON;

#include "../../core/Screen.hpp"
#include "../../misc/Debug.hpp"

MiniMap::MiniMap(ComponentContainer* c, const PixelRect& r) : MenuComponent(c, r)
{
	tileMapTexture = NULL;
}

void MiniMap::render() const
{
	if (tileMapTexture == NULL)
	{
		Screen::drawTextureID(VOID_ICON, getAbsoluteRect());
	}
	else
	{
		Screen::drawTexture(tileMapTexture, getAbsoluteRect());
	}
}
