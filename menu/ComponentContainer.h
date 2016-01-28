#ifndef __COMPONENTCONTAINER_CLASS__
#define __COMPONENTCONTAINER_CLASS__

#include <vector>

#include "MenuComponent.h"

class ComponentContainer
{
	public:
		std::vector<MenuComponent*> getComponents();
		virtual void render();
	private:
		std::vector<MenuComponent*> components;
};

#endif
