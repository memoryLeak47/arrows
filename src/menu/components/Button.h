#ifndef __BUTTON_CLASS__
#define __BUTTON_CLASS__

#include <string>

class PixelRect;

#include "../MenuComponent.h"

class Button : public MenuComponent
{
	public:
		Button(ComponentContainer*, const PixelRect&, const std::string&);
		virtual void render(); // override
	private:
		std::string caption;
};

#include "../../math/pixel/PixelRect.h"
#include "../../core/Screen.h"
#include "../../misc/Debug.h"

#endif
