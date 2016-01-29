#ifndef __MENU_CLASS__
#define __MENU_CLASS__

#include <string>
#include <SFML/Window.hpp>

#include "ComponentContainer.h"

class Menu : public ComponentContainer
{
	public:
		Menu(const PixelRect& rect); // windowed menu
		Menu(); // fullscreen window
		virtual bool isFullscreen();
		virtual void tick();
		void render();
		void onEvent(const sf::Event&);
	protected:
		static void popup(const std::string&);
	private:
		MenuComponent* getFocusedComponent();
		MenuComponent* focusedComponent;
};

#endif
