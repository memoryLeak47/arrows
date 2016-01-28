#include "ComponentContainer.h"

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
