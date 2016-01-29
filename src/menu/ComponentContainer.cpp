#include "ComponentContainer.h"

#include "../misc/Debug.h"
#include "../core/Screen.h"
#include "../math/pixel/PixelVector.h"

ComponentContainer::ComponentContainer(const PixelRect& rect) : MenuComponent(NULL, rect)
{
}

ComponentContainer::ComponentContainer(ComponentContainer* parent, const PixelRect& rect) : MenuComponent(parent, rect)
{
}

ComponentContainer::~ComponentContainer()
{
	components.clear();
}

void ComponentContainer::addComponent(MenuComponent* c)
{
	components.push_back(c);
}

const PixelVector& ComponentContainer::getCursorPosition() const
{
	PixelVector pos(Screen::getCursorPosition());
	return pos - getOffset();
}

MenuComponent* ComponentContainer::getHoveredComponent() const
{
/*	
	const PixelVector& cursor = getCursorPosition();
	if (cursor != PixelVector(-1, -1)) // wenn der cursor im fenster ist
	{
		for (int i = getComponents().size()-1; i >= 0; i--) // für alle Components (als letzes gerendert liegt ganz oben -> von hinten nach vorne)
		{
			if (cursor.inRect(*getComponents()[i])) // wenn die maus auf die Component zeigt
			{
				// und diese Component ein ComponentContainer ist der selbst eine gehoverte Component hat
				if (getComponents()[i] instanceof ComponentContainer && ((ComponentContainer*) getComponents()[i])->getHoveredComponent() != NULL)
				{
					// returne seine gehoverte Component
					return ((ComponentContainer) getComponents()[i]).getHoveredComponent();
				} // falls nicht
				return getComponents()[i]; // returne ihn selbst
			}
		} // wenn keine Component gefunden wurde
	} // oder die maus außerhalb des fensters ist

	
*/
	return NULL; // returne null
}

const std::vector<MenuComponent*>& ComponentContainer::getComponents() const
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
