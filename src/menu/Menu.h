#ifndef __MENU_CLASS__
#define __MENU_CLASS__

#include <string>

#include "ComponentContainer.h"

class Menu : public ComponentContainer
{
	public:
		Menu(const PixelRect& rect); // windowed menu
		Menu(); // fullscreen window
		virtual bool isFullscreen();
		virtual void tick();
		virtual void render();
	protected:
		static void popup(const std::string&);
};

#endif
