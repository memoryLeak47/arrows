#include "Menu.h"

bool Menu::isFullscreen() { return true; }

void Menu::tick()
{
	for (int i = 0; i < getComponents().size(); i++)
	{
		getComponents()[i]->tick();
	}
}

void Menu::render()
{
	// fill screen black
}
