#include "PopupMenu.hpp"

#include "../../core/Screen.hpp"
#include "../components/Panel.hpp"
#include "../components/Label.hpp"
#include "../components/BackButton.hpp"

PopupMenu::PopupMenu(const std::string& text)
	: Menu(PixelRect(Screen::getSize().getX()/2-200, Screen::getSize().getY()/2-150, 400, 300))
{
	this->text = text;
	addComponent(new Panel(this, PixelRect(PixelVector(0, 0), getRelativeRect().getSize())));
	addComponent(new Label(this, PixelRect(200-150, 20, 300, 20), text));
	addComponent(new BackButton(this, PixelVector(200-30, 50)));
}
