#include "EditField.h"

#include "../../misc/Debug.h"
#include "../../core/Screen.h"

EditField::EditField(ComponentContainer* parent, const PixelRect& rect, const std::string& s) : MenuComponent(parent, rect), caption(s)
{

}

EditField::EditField(ComponentContainer* parent, const PixelRect& rect) : MenuComponent(parent, rect), caption("")
{

}

void EditField::render()
{
	Screen::drawRect(*this, sf::Color::Blue);
	Screen::drawText(caption, getPosition(), sf::Color::Black);
}


