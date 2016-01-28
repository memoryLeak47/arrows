#include "Button.h"

#include "../../misc/Debug.h"
#include "../../core/Screen.h"

Button::Button(ComponentContainer* parent, const PixelRect& rect, const std::string& s) : MenuComponent(parent, rect), caption(s)
{

}

void Button::onClick() {}

void Button::render()
{
	Screen::drawRect(*this, sf::Color::Red);
	Screen::drawText(caption, getPosition(), sf::Color::Black);
}
