#ifndef __MENU_CLASS__
#define __MENU_CLASS__

#include "ComponentContainer.h"

class Menu : public ComponentContainer
{
	public:
		virtual bool isFullscreen();
		virtual void render();
};

#endif
