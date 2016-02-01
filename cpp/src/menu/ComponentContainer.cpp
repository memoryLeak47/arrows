#include "ComponentContainer.hpp"

#include "../misc/Debug.hpp"
#include "../core/Screen.hpp"
#include "../math/pixel/PixelVector.hpp"

ComponentContainer::ComponentContainer(const PixelRect& rect) : rect(rect)
{}

ComponentContainer::~ComponentContainer()
{
	components.clear();
}

void ComponentContainer::addComponent(MenuComponent* c)
{
	components.push_back(c);
}

PixelVector ComponentContainer::getCursorPosition() const
{
	return Screen::getCursorPosition() - getOffset();
}

MenuComponent* ComponentContainer::getHoveredComponent() const
{
	PixelVector cursor = getCursorPosition();

	if (cursor != PixelVector(-1, -1)) // wenn der cursor im fenster ist
	{
		for (int i = getComponents().size()-1; i >= 0; i--) // für alle Components (als letzes gerendert liegt ganz oben -> von hinten nach vorne)
		{
			if (cursor.inRect(getComponents()[i]->getRect())) // wenn die maus auf die Component zeigt
			{
				// returne ihn (falls er ein ComponentContainer ist, seine hovered-component)
				return getComponents()[i]->getHoveredComponentRecursively();
			}
		} // wenn keine Component gefunden wurde
	} // oder die maus außerhalb des fensters ist

	return NULL; // returne null
}

PixelRect ComponentContainer::getRect() const { return rect; }

void ComponentContainer::setRect(const PixelRect& r) { rect = r; }

std::vector<MenuComponent*> ComponentContainer::getComponents() const
{
	return components;
}

void ComponentContainer::render() const
{
	for (int i = 0; i < getComponents().size(); i++)
	{
		getComponents()[i]->render();
	}
}

PixelVector ComponentContainer::getOffset() const
{
	return getRect().getPosition();
}
