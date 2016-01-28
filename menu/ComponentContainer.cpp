#include "ComponentContainer.h"

ComponentContainer::ComponentContainer(const PixelRect& rect) : PixelRect(rect)
{
	
}

ComponentContainer::ComponentContainer(const ComponentContainer& parent, const PixelRect& rect) : PixelRect(rect)
{
	this->parent = (ComponentContainer*) &parent;
}

std::vector<MenuComponent*> ComponentContainer::getComponents()
{
	return components;
}

void ComponentContainer::render()
{
	for (int i = 0; i < getComponents().size(); i++)
	{
		getComponents()[i]->render();
	}
}
