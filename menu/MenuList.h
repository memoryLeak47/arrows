#ifndef __MENULIST_CLASS__
#define __MENULIST_CLASS__

#include <list>
#include <SFML/Window.hpp>

#include "Menu.h"

class MenuList
{
	public:
		MenuList();
		void onEvent(const sf::Event &event);
	private:
		std::list<Menu*> menues;
};

#endif
