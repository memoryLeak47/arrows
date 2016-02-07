#ifndef __COMPONENTCONTAINER_CLASS__
#define __COMPONENTCONTAINER_CLASS__

#include <vector>

#include "../math/pixel/PixelRect.hpp"

class MenuComponent;

class ComponentContainer
{
	public:
		ComponentContainer();
		virtual ~ComponentContainer();
		PixelVector getRelativeCursorPosition() const;
		virtual void render() const;
		virtual PixelRect getAbsoluteRect() const = 0;
		virtual PixelRect getRelativeRect() const = 0;
		virtual std::vector<MenuComponent*>* getComponents() const = 0;
	protected:
		void addComponent(MenuComponent*);
		MenuComponent* getHoveredComponent() const;
};

#include "MenuComponent.hpp"

#endif
