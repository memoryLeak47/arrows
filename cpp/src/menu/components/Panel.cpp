#include "Panel.hpp"

#include <algorithm>

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

void Panel::calcSize()
{
	int right = 0;
	int bot = 0;

	// sucht die width/height indem alle Komponenten durchlaufen werden und die am weitesten rechts und unten gespeichert werden
	for (int i = 0; i < getComponents().size(); i++)
	{
		right = std::max(right, getComponents()[i]->getRect().getRight() + getPadding().getX());
		bot = std::max(bot, getComponents()[i]->getRect().getBot() + getPadding().getY());
	}

	if (right != getRect().getSize().getX())
	{
		setRect(PixelRect(
			getRect().getPosition().getX(),
			getRect().getPosition().getY(),
			right,
			getRect().getSize().getY()));
	}

	if (bot != getRect().getSize().getY())
	{
		setRect(PixelRect(
			getRect().getPosition().getX(),
			getRect().getPosition().getY(),
			getRect().getSize().getX(),
			bot));
	}
}

PixelVector Panel::getPadding() const { return PixelVector(20, 20); }
