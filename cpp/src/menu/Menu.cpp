#include "Menu.hpp"

#include <misc/Global.hpp>
#include <menu/MenuList.hpp>
#include <core/Screen.hpp>
#include <core/Main.hpp>
#include "menues/PopupMenu.hpp"

Menu::Menu(const PixelRect& rect)
	: focusedComponent(NULL), rect(rect)
{}

Menu::Menu()
	: focusedComponent(NULL), rect(PixelRect(0, 0, Screen::getSize().x, Screen::getSize().y))
{}

bool Menu::isFullscreen() { return getRelativeRect() == PixelRect(0, 0, Screen::getSize().x, Screen::getSize().y); }

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
	}
	else if (event.type ==  sf::Event::MouseButtonReleased) // wenn die maus losgelassen wurde
	{
		MenuComponent* hovered = getHoveredComponent();
		if (hovered != NULL) // und es eine gehoverte MenuComponent gibt
		{
			hovered->onClick(((const sf::Event::MouseButtonEvent&) event).button); // gebe das 
		}
	}
	// IMPORTANT-NOTE: the game-intern key-events are handled by sf::Keyboard::isKeyPressed(sf::Keyboard::Key) !!!
	else if (event.type == sf::Event::TextEntered) // wenn die tastatur gedrückt wurde
	{
		if (getFocusedComponent() != NULL) // und es eine fokusierte MenuComponent gibt 
		{
			if (event.text.unicode < 128)
			{
				getFocusedComponent()->onTextEntered(static_cast<char>(event.text.unicode)); // gebe d
			}
		}
	}
	else // falls das event ein anderes ist
	{
		if (TAG_EVENT) Debug::warn("bad Event-subclass"); // printe nen error und beende das programm
	}
}

void Menu::tick()
{
	for (unsigned int i = 0; i < getComponents().size(); i++)
	{
		getComponents()[i]->tick();
	}
}

void Menu::render() const
{
	// fill screen black
	ComponentContainer::render();
}

void Menu::popup(const std::string& text)
{
	Main::getMenuList()->addMenu(new PopupMenu(text));
}

MenuComponent* Menu::getFocusedComponent()
{
	return focusedComponent;
}

PixelRect Menu::getAbsoluteRect() const
{
	return getRelativeRect();
}

PixelRect Menu::getRelativeRect() const
{
	return rect;
}
