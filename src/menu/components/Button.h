#ifndef __BUTTON_CLASS__
#define __BUTTON_CLASS__

#include <string>

#include "../MenuComponent.h"

class PixelRect;

class Button : public MenuComponent
{
	public:
		Button(ComponentContainer*, const PixelRect&, const std::string&);
		virtual void render(); // override
	private:
		std::string caption;
};

#include "../../math/pixel/PixelRect.h"

#endif
