#ifndef __MENUCOMPONENT_CLASS__
#define __MENUCOMPONENT_CLASS__

#include "../math/pixel/PixelRect.h"
#include "ComponentContainer.h"

class MenuComponent : public PixelRect
{
	public:
		MenuComponent(ComponentContainer* parent, const PixelRect&);
		virtual void tick();
		virtual void render() = 0;
	private:
		ComponentContainer* parent;
};


#endif
