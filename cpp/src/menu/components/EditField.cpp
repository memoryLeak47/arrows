#include "EditField.h"

#include "../../misc/Debug.h"
#include "../../core/Screen.h"

EditField::EditField(ComponentContainer* parent, const PixelRect& rect, const std::string& s) : MenuComponent(parent, rect), text(s)
{

}

EditField::EditField(ComponentContainer* parent, const PixelRect& rect) : MenuComponent(parent, rect), text("")
{

}

void EditField::onTextEntered(char c)
{
	if (c == 8)
	{
		text = text.substr(0, text.length()-1);
	}
	else
	{
		text += c;
	}
}

void EditField::render() const
{
	Screen::drawRect(getRect(), sf::Color::Blue);
	Screen::drawText(text, getRect().getPosition(), sf::Color::Black);
}

const std::string& EditField::getText() const { return text; }
