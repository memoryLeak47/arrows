#include "Button.hpp"

#include "../../misc/Debug.hpp"
#include "../../core/Screen.hpp"

Button::Button(ComponentContainer* parent, const PixelRect& rect, const std::string& s) : MenuComponent(parent, rect), text(s)
{}

void Button::render() const
{
	Screen::drawRect(getAbsoluteRect(), sf::Color::Red);
	Screen::drawText(getText(), getAbsoluteRect().getPosition(), sf::Color::Black);
}

std::string Button::getText() const
{
	return text;
}
