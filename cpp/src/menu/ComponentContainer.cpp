#include "ComponentContainer.hpp"

#include <misc/Global.hpp>
#include <core/Main.hpp>
#include <core/Screen.hpp>
#include <math/pixel/PixelVector.hpp>
#include "MenuComponent.hpp"

ComponentContainer::ComponentContainer()
{}

ComponentContainer::~ComponentContainer()
{
	clearComponents();
}

const std::vector<MenuComponent*>& ComponentContainer::getComponents() const
{
	return components;
}

void ComponentContainer::addComponent(MenuComponent* c)
{
	components.push_back(c);
}

void ComponentContainer::clearComponents()
{
	deleteAndClearVector(components);
}

PixelVector ComponentContainer::getRelativeCursorPosition() const
{
	return Screen::getCursorPosition() - getAbsoluteRect().getPosition();
}

MenuComponent* ComponentContainer::getHoveredComponent() const
{
	PixelVector cursor = getRelativeCursorPosition();

	for (int i = getComponents().size()-1; i >= 0; i--) // für alle Components (als letzes gerendert liegt ganz oben -> von hinten nach vorne)
	{
		if (cursor.inRect(getComponents()[i]->getRelativeRect())) // wenn die maus auf die Component zeigt
		{
			// returne ihn (falls er ein ComponentContainer ist, seine hovered-component)
			return getComponents()[i]->getHoveredComponentRecursively();
		}
	} // wenn keine Component gefunden wurde
	return nullptr;
}

void ComponentContainer::render() const
{
	for (unsigned int i = 0; i < getComponents().size(); i++)
	{
		getComponents()[i]->render();
	}
}
