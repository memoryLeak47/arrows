#ifndef __MENU_CLASS__
#define __MENU_CLASS__

#include "ComponentContainer.h"

class Menu : public ComponentContainer
{
	public:
		Menu(const PixelRect& rect);
		virtual bool isFullscreen();
		virtual void tick();
		virtual void render();
};

#endif
