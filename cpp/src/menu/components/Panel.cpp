#include "Panel.hpp"

#include "../../core/Screen.hpp"

Panel::Panel(ComponentContainer* c, const PixelRect& r) : MenuComponent(c, r), ComponentContainer(r)
{}

MenuComponent* Panel::getHoveredComponentRecursively() const
{
	return ComponentContainer::getHoveredComponent();
}

void Panel::render() const
{
	Screen::drawRect(getRect(), sf::Color(255, 255, 255, 40));
	ComponentContainer::render();
}

PixelVector Panel::getOffset() const
{
	return getParent()->getOffset() + getRect().getPosition();
}
