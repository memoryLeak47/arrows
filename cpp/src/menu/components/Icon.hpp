#ifndef __ICON_CLASS__
#define __ICON_CLASS__

#include "../../graphics/GraphicsManager.hpp"

#include "../MenuComponent.hpp"

class Icon : public MenuComponent
{
	public:
		Icon(ComponentContainer*, const PixelRect&);
		virtual void render() const override;
		virtual GraphicsID getGraphicsID() const = 0;
};

#endif
