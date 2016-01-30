#ifndef __PANEL_CLASS__
#define __PANEL_CLASS__

#include "../MenuComponent.h"
#include "../ComponentContainer.h"

class Panel : public MenuComponent, public ComponentContainer
{
	public:
		Panel(ComponentContainer*, const PixelRect&);
		virtual void render() const override;
		virtual const PixelVector& getOffset() const override;
};

#endif
