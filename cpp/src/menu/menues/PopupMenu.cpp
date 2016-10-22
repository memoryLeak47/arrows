#include "PopupMenu.hpp"

#include <core/Screen.hpp>
#include <menu/MenuList.hpp>
#include <menu/components/Panel.hpp>
#include <menu/components/Label.hpp>
#include <menu/components/BackButton.hpp>

PopupMenu::PopupMenu(const std::string& text)
	: Menu(PixelRect(Screen::getSize().x/2-200, Screen::getSize().y/2-150, 400, 300))
{
	this->text = text;
	addComponent(new Panel(this, PixelRect(PixelVector(0, 0), getRelativeRect().getSize())));
	addComponent(new Label(this, PixelRect(200-150, 20, 300, 20), text));
	addComponent(new BackButton(this, PixelVector(200-30, 50)));
}
