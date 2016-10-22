#ifndef __MENULIST_CLASS__
#define __MENULIST_CLASS__

class Menu;

#include <SFML/Window/Event.hpp>
#include <vector>

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
	private:
		std::vector<Menu*> menues;
		const std::vector<Menu*>& getMenues() const;
		Menu* getTopmostMenu();
		int getTopmostFullscreenMenuIndex() const;
};

#endif
