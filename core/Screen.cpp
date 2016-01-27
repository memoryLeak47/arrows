#include "Screen.h"

sf::RenderWindow* Screen::window;

void Screen::init()
{
	window = new sf::RenderWindow(sf::VideoMode(800, 600), "Arrows");
}

void Screen::uninit()
{
	delete window;
}
