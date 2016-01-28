#ifndef __COMPONENTCONTAINER_CLASS__
#define __COMPONENTCONTAINER_CLASS__

#include <vector>

#include "../math/pixel/PixelRect.h"
class MenuComponent;

class ComponentContainer : public PixelRect
{
	public:
		ComponentContainer(const PixelRect& rect); // for menues ..
		ComponentContainer(const ComponentContainer& parent, const PixelRect& rect); // for panels ...
		~ComponentContainer();
		const std::vector<MenuComponent*>& getComponents() const;
		virtual void render() const;
	protected:
		void addComponent(MenuComponent*);
	private:
		std::vector<MenuComponent*> components;
		ComponentContainer* parent;
};

#include "../misc/Debug.h"
#include "MenuComponent.h"

#endif
