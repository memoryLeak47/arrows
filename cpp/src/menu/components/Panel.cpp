#include "Panel.h"

Panel::Panel(ComponentContainer* c, const PixelRect& r) : MenuComponent(c, r), ComponentContainer(r)
{}

void Panel::render() const
{
	ComponentContainer::render();
}

const PixelVector& Panel::getOffset() const
{
	return getParent()->getOffset();
}
