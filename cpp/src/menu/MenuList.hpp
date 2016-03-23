#ifndef __MENULIST_CLASS__
#define __MENULIST_CLASS__

#include <vector>
#include <SFML/Window.hpp>

class Menu;
class NetworkingMenu;

class MenuList
{
	public:
		MenuList();
		virtual ~MenuList();
		void onEvent(const sf::Event &event);
		void tick();
		void render();
		void addMenu(Menu*);
		void back(); // removes menu
		NetworkingMenu* getNetworkingMenu();
	private:
		std::vector<Menu*> menues;
		std::vector<Menu*> getMenues(); // TODO correct data type?
		Menu* getTopmostMenu();
		int getTopmostFullscreenMenuIndex();
};

#include "Menu.hpp"
#include "NetworkingMenu.hpp"

#endif
