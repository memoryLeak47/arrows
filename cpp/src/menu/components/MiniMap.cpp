#include "MiniMap.h"

#include "../../core/Screen.h"
#include "../../misc/Debug.h"

MiniMap::MiniMap(ComponentContainer* c, const PixelRect& r) : MenuComponent(c, r)
{}

void MiniMap::render() const
{
	Screen::drawImage(tileMapImage, getRect());
}
