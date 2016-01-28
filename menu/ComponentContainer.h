#ifndef __COMPONENTCONTAINER_CLASS__
#define __COMPONENTCONTAINER_CLASS__

#include <vector>

#include "MenuComponent.h"
#include "../math/pixel/PixelRect.h"

class ComponentContainer : public PixelRect
{
	public:
		ComponentContainer(const PixelRect& rect);
		ComponentContainer(const ComponentContainer& parent, const PixelRect& rect);
		std::vector<MenuComponent*> getComponents();
		virtual void render();
	private:
		std::vector<MenuComponent*> components;
		ComponentContainer* parent;
};

#endif
