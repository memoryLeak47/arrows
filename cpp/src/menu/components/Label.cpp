#include "Label.h"

#include "../../misc/Debug.h"
#include "../../core/Screen.h"

Label::Label(ComponentContainer* parent, const PixelRect& rect, const std::string& s) : MenuComponent(parent, rect), caption(s)
{

}

void Label::render() const
{
	Screen::drawRect(getRect(), sf::Color::Green);
	Screen::drawText(caption, getRect().getPosition(), sf::Color::Black);
}
