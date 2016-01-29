#ifndef __COMPONENTCONTAINER_CLASS__
#define __COMPONENTCONTAINER_CLASS__

#include <vector>

#include "../math/pixel/PixelRect.h"

class MenuComponent;

class ComponentContainer : public PixelRect
{
	public:
		ComponentContainer(const PixelRect& rect);
		~ComponentContainer();
		const std::vector<MenuComponent*>& getComponents() const;
		const PixelVector& getCursorPosition() const;
		virtual void render() const;
		const PixelVector& getOffset() const;
	protected:
		void addComponent(MenuComponent*);
		MenuComponent* getHoveredComponent() const;
	private:
		std::vector<MenuComponent*> components;
};

#include "MenuComponent.h"

#endif
