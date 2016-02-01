#ifndef __COMPONENTCONTAINER_CLASS__
#define __COMPONENTCONTAINER_CLASS__

#include <vector>

#include "../math/pixel/PixelRect.hpp"

class MenuComponent;

class ComponentContainer
{
	public:
		ComponentContainer(const PixelRect& rect);
		~ComponentContainer();
		std::vector<MenuComponent*> getComponents() const;
		PixelVector getCursorPosition() const;
		virtual void render() const;
		virtual PixelVector getOffset() const;
		PixelRect getRect() const;
	protected:
		void setRect(const PixelRect&);
		void addComponent(MenuComponent*);
		MenuComponent* getHoveredComponent() const;
	private:
		PixelRect rect;
		std::vector<MenuComponent*> components;
};

#include "MenuComponent.hpp"

#endif
