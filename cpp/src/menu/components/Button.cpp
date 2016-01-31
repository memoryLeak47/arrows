#include "Button.hpp"

#include "../../misc/Debug.hpp"
#include "../../core/Screen.hpp"

Button::Button(ComponentContainer* parent, const PixelRect& rect, const std::string& s) : MenuComponent(parent, rect), caption(s)
{

}

void Button::render() const
{
	Screen::drawRect(getRect(), sf::Color::Red);
	Screen::drawText(caption, getRect().getPosition(), sf::Color::Black);
}
