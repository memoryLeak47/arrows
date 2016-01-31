#include "MiniMap.hpp"

#include "../../core/Screen.hpp"
#include "../../misc/Debug.hpp"

MiniMap::MiniMap(ComponentContainer* c, const PixelRect& r) : MenuComponent(c, r)
{}

void MiniMap::render() const
{
	Screen::drawImage(tileMapImage, getRect());
}
