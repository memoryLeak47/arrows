#ifndef __COMPONENTCONTAINER_CLASS__
#define __COMPONENTCONTAINER_CLASS__

#include <vector>

#include "MenuComponent.h"

class ComponentContainer
{
	private:
		std::vector<MenuComponent*> components;
};

#endif
