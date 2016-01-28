#include "Label.h"

#include "../../misc/Debug.h"
#include "../../core/Screen.h"

Label::Label(ComponentContainer* parent, const PixelRect& rect, const std::string& s) : MenuComponent(parent, rect), caption(s)
{

}

void Label::render()
{
	Screen::drawRect(*this, sf::Color::Green);
	Screen::drawText(caption, getPosition(), sf::Color::Black);
}
