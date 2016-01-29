#include "Menu.h"

#include "../misc/Debug.h"
#include "../core/Main.h"

Menu::Menu(const PixelRect& rect) : ComponentContainer(rect)
{
	
}

Menu::Menu() : ComponentContainer(PixelRect(0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y))
{
}

bool Menu::isFullscreen() { return true; }

void Menu::onEvent(const sf::Event& event)
{
	if (event.type == sf::Event::MouseMoved) // wenn sich die maus bewegt hat
	{
		MenuComponent* hovered = getHoveredComponent(); // Verhinderung einer null-pointer-exception
		if (hovered != NULL) // und es eine gehoverte MenuComponent gibt
		{
			int x = ((const sf::Event::MouseMoveEvent&) event).x;
			int y = ((const sf::Event::MouseMoveEvent&) event).y;
			hovered->onMouseMove(PixelVector(x, y)); // gebe das event an sie weiter
		}
	}
	else if (event.type == sf::Event::MouseButtonPressed) // wenn die maus gedrückt wurde
	{
		focusedComponent = getHoveredComponent(); // lasse die fokusierte MenuComponent die gehov
		if (getHoveredComponent() == NULL)
		{
		}
	}
	else if (event.type ==  sf::Event::MouseButtonReleased) // wenn die maus losgelassen wurde
	{
		MenuComponent* hovered = getHoveredComponent();
		if (hovered != NULL) // und es eine gehoverte MenuComponent gibt
		{
			hovered->onClick(((const sf::Event::MouseButtonEvent&) event).button); // gebe das 
		}
	}
	else if (event.type == sf::Event::KeyPressed) // wenn die tastatur gedrückt wurde
	{
		if (getFocusedComponent() != NULL) // und es eine fokusierte MenuComponent gibt 
		{
			getFocusedComponent()->onKeyPress(((const sf::Event::KeyEvent&) event).code); // gebe d
		}
	}
	else if (event.type == sf::Event::KeyReleased) // wenn die tastatur losgelassen wurde
	{
		if (getFocusedComponent() != NULL) // und es eine fokusierte MenuComponent gibt
		{
			getFocusedComponent()->onKeyRelease(((const sf::Event::KeyEvent&) event).code); // ge
		}
	}
	else // falls das event ein anderes ist
	{
		Debug::warn("bad Event-subclass"); // printe nen error und beende das programm
	}
}

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

void Menu::popup(const std::string& msg)
{
	Debug::note("Popupwindow: " + msg);
}

MenuComponent* Menu::getFocusedComponent()
{
	return focusedComponent;
}

