#ifndef __COMPONENTCONTAINER_CLASS__
#define __COMPONENTCONTAINER_CLASS__

#include <vector>

class PixelRect;
#include "MenuComponent.h"

class ComponentContainer : public MenuComponent
{
	public:
		ComponentContainer(const PixelRect& rect); // for menues ..
		ComponentContainer(ComponentContainer* parent, const PixelRect& rect); // for panels ...
		~ComponentContainer();
		const std::vector<MenuComponent*>& getComponents() const;
		const PixelVector& getCursorPosition() const;
		virtual void render() const;
	protected:
		void addComponent(MenuComponent*);
		MenuComponent* getHoveredComponent() const;
	private:
		std::vector<MenuComponent*> components;
};

#include "../math/pixel/PixelRect.h"

#endif
