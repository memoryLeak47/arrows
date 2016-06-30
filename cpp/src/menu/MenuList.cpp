#include "MenuList.hpp"

#include "../misc/Global.hpp"
#include "menues/LoginMenu.hpp"
#include "../core/Main.hpp"

MenuList::MenuList()
{
	menues.push_back(new LoginMenu());
}

MenuList::~MenuList()
{
	deleteAndClearVector(menues);
}

void MenuList::onEvent(const sf::Event &event)
{
	if (!global::DEBUG_STEPWISE)
	{
		getTopmostMenu()->onEvent(event);
	}
	else
	{
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return)
		{
			getTopmostMenu()->tick();
		}
		else
		{
			getTopmostMenu()->onEvent(event);
		}
	}
}

void MenuList::tick()
{
	if (!global::DEBUG_STEPWISE)
	{
		getTopmostMenu()->tick();
	}
}

void MenuList::render()
{
	for (unsigned int i = getTopmostFullscreenMenuIndex(); i < getMenues().size(); i++)
	// für alle menues die auf dem obersten fullscreen menu liegen (und dem obersten fullscreen-menu)
	{
		getMenues()[i]->render(); // render
	}
}

void MenuList::addMenu(Menu* menu)
{
	menues.push_back(menu);
}

void MenuList::back()
{
	deleteAndNULL(menues[menues.size()-1]);
	menues.pop_back();
}

NetworkingMenu* MenuList::getNetworkingMenu()
{
	for (int i = getMenues().size()-1; i > 1 /* NOT login/main-menu */; i--)
	{
		if (getMenues()[i]->isNetworkingMenu())
		{
			return (NetworkingMenu*) getMenues()[i];
		}
	}
	return NULL;
}

std::vector<Menu*> MenuList::getMenues()
{
	return menues;
}

// bekomme oberstes menu
Menu* MenuList::getTopmostMenu()
{
	return menues.back();
}

// returne den index des obersten menues
int MenuList::getTopmostFullscreenMenuIndex()
{
	for (int i = getMenues().size()-1; i >= 0; i--) // für alle menues (von hinten nach vorne)
	{
		if (getMenues()[i]->isFullscreen()) // wenn du fullscreen bist
		{
			return i; // returne deinen index
		}
	} // wenn keins fullscreen ist
	Debug::error("MenuList.getTopmostFullscreenMenuIndex() no fullscreen menu!"); // beende das programm und schmeiß nen error
	return 0;
}

