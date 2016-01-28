#ifndef __MENULIST_CLASS__
#define __MENULIST_CLASS__

#include <vector>
#include <SFML/Window.hpp>

#include "Menu.h"
#include "menues/LoginMenu.h"
#include "../misc/Debug.h"

class MenuList
{
	public:
		MenuList();
		void onEvent(const sf::Event &event);
		void tick();
		void render();
	private:
		std::vector<Menu*> menues;
		std::vector<Menu*> getMenues();
		Menu* getTopmostMenu();
		int getTopmostFullscreenMenuIndex();
};

#endif
