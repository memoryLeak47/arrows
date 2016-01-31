#ifndef __PANEL_CLASS__
#define __PANEL_CLASS__

#include "../MenuComponent.hpp"
#include "../ComponentContainer.hpp"

class Panel : public MenuComponent, public ComponentContainer
{
	using ComponentContainer::getRect;
	public:
		Panel(ComponentContainer*, const PixelRect&);
		MenuComponent* getHoveredComponentRecursively() const override;
		virtual void render() const override;
		virtual PixelVector getOffset() const override;
};

#endif
