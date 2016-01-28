#ifndef __MENULIST_CLASS__
#define __MENULIST_CLASS__

#include <vector>
#include <SFML/Window.hpp>

class Menu;

class MenuList
{
	public:
		MenuList();
		~MenuList();
		void onEvent(const sf::Event &event);
		void tick();
		void render();
	private:
		std::vector<Menu*> menues;
		std::vector<Menu*> getMenues();
		Menu* getTopmostMenu();
		int getTopmostFullscreenMenuIndex();
};

#include "Menu.h"

#endif
