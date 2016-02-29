#include "Panel.hpp"

#include <algorithm>

#include "../../core/Screen.hpp"

Panel::Panel(ComponentContainer* c, const PixelRect& r)
	: MenuComponent(c, r)
{}

PixelRect Panel::getAbsoluteRect() const
{
	return MenuComponent::getAbsoluteRect();
}

PixelRect Panel::getRelativeRect() const
{
	return MenuComponent::getRelativeRect();
}

MenuComponent* Panel::getHoveredComponentRecursively() const
{
	return ComponentContainer::getHoveredComponent();
}

void Panel::render() const
{
	Screen::fillRect(getAbsoluteRect(), sf::Color(255, 255, 255, 40));
	ComponentContainer::render();
}

void Panel::calcSize()
{
	int width = 0;
	int height = 0;

	// sucht die width/height indem alle Komponenten durchlaufen werden und die am weitesten rechts und unten gespeichert werden
	for (int i = 0; i < getComponents().size(); i++)
	{
		width = std::max(width, getComponents()[i]->getRelativeRect().getRight() + getPadding().getX());
		height = std::max(height, getComponents()[i]->getRelativeRect().getBot() + getPadding().getY());
	}

	if (width != getRelativeRect().getSize().getX())
	{
		setRelativeRect(PixelRect(
			getRelativeRect().getPosition().getX(),
			getRelativeRect().getPosition().getY(),
			width,
			getRelativeRect().getSize().getY()));
	}

	if (height != getRelativeRect().getSize().getY())
	{
		setRelativeRect(PixelRect(
			getRelativeRect().getPosition().getX(),
			getRelativeRect().getPosition().getY(),
			getRelativeRect().getSize().getX(),
			height));
	}
}

PixelVector Panel::getPadding() const { return PixelVector(20, 20); }
