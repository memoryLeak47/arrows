#ifndef __PANEL_CLASS__
#define __PANEL_CLASS__

#include "../MenuComponent.hpp"
#include "../ComponentContainer.hpp"

class Panel : public MenuComponent, public ComponentContainer
{
	public:
		using ComponentContainer::getRect;
		using ComponentContainer::setRect;
		Panel(ComponentContainer*, const PixelRect&);
		MenuComponent* getHoveredComponentRecursively() const override;
		virtual void render() const override;
		virtual PixelVector getOffset() const override;
		void calcSize();
		virtual PixelVector getPadding() const;
};

#endif
