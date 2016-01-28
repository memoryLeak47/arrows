#ifndef __COMPONENTCONTAINER_CLASS__
#define __COMPONENTCONTAINER_CLASS__

#include <vector>

#include "../math/pixel/PixelRect.h"
class MenuComponent;

class ComponentContainer : public PixelRect
{
	public:
		ComponentContainer(const PixelRect& rect);
		ComponentContainer(const ComponentContainer& parent, const PixelRect& rect);
		const std::vector<MenuComponent*>& getComponents() const;
		virtual void render() const;
	protected:
		void addComponent(MenuComponent*);
	private:
		std::vector<MenuComponent*> components;
		ComponentContainer* parent;
};

#include "MenuComponent.h"

#endif
