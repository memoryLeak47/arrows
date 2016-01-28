#include "Menu.h"

Menu::Menu(const PixelRect& rect) : ComponentContainer(rect)
{
	
}

Menu::Menu() : ComponentContainer(PixelRect(0, 0, 800, 600))
{
}

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
	ComponentContainer::render();
}
