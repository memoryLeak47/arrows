#ifndef __LABEL_CLASS__
#define __LABEL_CLASS__

#include <string>

#include "../MenuComponent.h"

class PixelRect;

class Label : public MenuComponent
{
	public:
		Label(ComponentContainer*, const PixelRect&, const std::string&);
		void render(); // override
	private:
		std::string caption;
	
};

#include "../../math/pixel/PixelRect.h"

#endif
