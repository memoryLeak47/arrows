#include "Screen.h"

sf::RenderWindow* Screen::window;

void Screen::init()
{
	Screen::window = new sf::RenderWindow(sf::VideoMode(800, 600), "Arrows");
}
