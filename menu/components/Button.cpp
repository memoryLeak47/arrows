#include "Button.h"

Button::Button()
{
}

void Button::render()
{
	Screen::drawRect(PixelRect(20, 20, 20, 20), sf::Color::Red);
}
