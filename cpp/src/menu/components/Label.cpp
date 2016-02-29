#include "Label.hpp"

#include "../../misc/Debug.hpp"
#include "../../core/Screen.hpp"

Label::Label(ComponentContainer* parent, const PixelRect& rect, const std::string& s) : MenuComponent(parent, rect), caption(s)
{

}

void Label::render() const
{
	Screen::fillRect(getAbsoluteRect(), sf::Color::Green);
	Screen::drawText(caption, getAbsoluteRect().getPosition(), sf::Color::Black);
}
