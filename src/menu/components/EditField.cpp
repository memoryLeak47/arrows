#include "EditField.h"

#include "../../misc/Debug.h"
#include "../../core/Screen.h"

EditField::EditField(ComponentContainer* parent, const PixelRect& rect, const std::string& s) : MenuComponent(parent, rect), text(s)
{

}

EditField::EditField(ComponentContainer* parent, const PixelRect& rect) : MenuComponent(parent, rect), text("")
{

}

void EditField::render()
{
	Screen::drawRect(*this, sf::Color::Blue);
	Screen::drawText(text, getPosition(), sf::Color::Black);
}

const std::string& EditField::getText() const { return text; }
