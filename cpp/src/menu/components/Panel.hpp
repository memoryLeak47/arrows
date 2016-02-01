#ifndef __PANEL_CLASS__
#define __PANEL_CLASS__

#include "../MenuComponent.hpp"
#include "../ComponentContainer.hpp"

class Panel : public MenuComponent, public ComponentContainer
{
	public:
		Panel(ComponentContainer*, const PixelRect&);
		MenuComponent* getHoveredComponentRecursively() const override;
		virtual void render() const override;
		virtual PixelVector getOffset() const override;
		PixelRect getRect() const;
		void calcSize();
		virtual PixelVector getPadding() const;
};

#endif
