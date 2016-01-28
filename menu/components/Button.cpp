#include "Button.h"

Button::Button(ComponentContainer* parent, const PixelRect& rect, const std::string& s) : MenuComponent(parent, rect), string(s)
{
}

void Button::render()
{
	Screen::drawRect(PixelRect(20, 20, 20, 20), sf::Color::Red);
}
