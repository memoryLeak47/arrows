#include "ComponentContainer.h"

ComponentContainer::ComponentContainer(const PixelRect& rect) : PixelRect(rect)
{
	
}

ComponentContainer::ComponentContainer(const ComponentContainer& parent, const PixelRect& rect) : PixelRect(rect)
{
	this->parent = (ComponentContainer*) &parent;
}

ComponentContainer::~ComponentContainer()
{
	components.clear();
}

void ComponentContainer::addComponent(MenuComponent* c)
{
	components.push_back(c);
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
