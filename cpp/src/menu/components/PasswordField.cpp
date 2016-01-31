#include "PasswordField.h"

#include "../../misc/Debug.h"
#include "../../core/Screen.h"

PasswordField::PasswordField(ComponentContainer* parent, const PixelRect& rect, const std::string& s) : MenuComponent(parent, rect), text(s)
{

}

PasswordField::PasswordField(ComponentContainer* parent, const PixelRect& rect) : MenuComponent(parent, rect), text("")
{

}

void PasswordField::onTextEntered(char c)
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

void PasswordField::render() const
{
	Screen::drawRect(getRect(), sf::Color::Blue);
	std::string renderedText = "";
	for (int i = 0; i < getText().length(); i++)
	{
		renderedText += "*";
	}

	Screen::drawText(renderedText, getRect().getPosition(), sf::Color::Black);
}

const std::string& PasswordField::getText() const { return text; }
