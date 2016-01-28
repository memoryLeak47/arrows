#ifndef __MENUCOMPONENT_CLASS__
#define __MENUCOMPONENT_CLASS__

#include "../math/pixel/PixelRect.h"

class ComponentContainer;

class MenuComponent : public PixelRect
{
	public:
		MenuComponent(ComponentContainer* parent, const PixelRect&);
		~MenuComponent();
		virtual void tick();
		virtual void render() = 0;
	protected:
		ComponentContainer* getParent();
	private:
		ComponentContainer* parent;
};

#include "ComponentContainer.h"

#endif
