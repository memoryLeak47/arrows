#include "Icon.hpp"

#include <core/Screen.hpp>
#include <misc/Debug.hpp>

Icon::Icon(ComponentContainer* c, const PixelRect& r) : MenuComponent(c, r)
{}

void Icon::render() const
{
	Screen::drawGraphicsID(getAbsoluteRect(), getTextureID());
}


