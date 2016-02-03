#ifndef __ICON_CLASS__
#define __ICON_CLASS__

#include "../MenuComponent.hpp"

class ImageID;

class Icon : public MenuComponent
{
	public:
		Icon(ComponentContainer*, const PixelRect&);
		virtual void render() const override;
		virtual ImageID getImageID() const = 0;
};

#include "../../graphics/ImageID.hpp"

#endif
