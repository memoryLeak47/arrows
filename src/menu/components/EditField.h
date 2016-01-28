#ifndef __EDITFIELD_CLASS__
#define __EDITFIELD_CLASS__

#include <string>

#include "../MenuComponent.h"

class PixelRect;

class EditField : public MenuComponent
{
	public:
		EditField(ComponentContainer*, const PixelRect&, const std::string&);
		EditField(ComponentContainer*, const PixelRect&);
		void render(); // override
	private:
		std::string caption;
	
};

#include "../../math/pixel/PixelRect.h"

#endif
