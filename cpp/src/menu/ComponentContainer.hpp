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
		PixelVector getRelativeCursorPosition() const;
		virtual void render() const;
		PixelRect getAbsoluteRect() const;
		PixelRect getRelativeRect() const;
	protected:
		void setRelativeRect(const PixelRect&);
		void addComponent(MenuComponent*);
		MenuComponent* getHoveredComponent() const;
	private:
		PixelRect rect; // relative rect
		std::vector<MenuComponent*> components;
};

#include "MenuComponent.hpp"

#endif
