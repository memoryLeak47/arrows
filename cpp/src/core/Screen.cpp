#include "Screen.hpp"

#include "../misc/Debug.hpp"
#include "Main.hpp"

sf::RenderWindow* Screen::window;
sf::Text Screen::text;

void Screen::init()
{
	window = new sf::RenderWindow(sf::VideoMode(SCREEN_SIZE_X, SCREEN_SIZE_Y), "Arrows", sf::Style::Fullscreen);
	static sf::Font font;
	if (!font.loadFromFile("res/fonts/font.ttf"))
	{
		Debug::warn("couldn't load font");
	}
	else
	{
		text.setFont(font);
		text.setCharacterSize(15);
	}
}

void Screen::uninit()
{
	window->close();
	delete window;
}

void Screen::tick()
{
	static sf::Event event;
	if (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			Main::exit();
		}
		else
		{
			Main::getMenuList()->onEvent(event);
		}
	}
}

void Screen::display()
{
	window->display();
	window->clear(sf::Color(20, 20, 20));
}

PixelVector Screen::getCursorPosition()
{
	int x = sf::Mouse::getPosition().x;
	int y = sf::Mouse::getPosition().y;
	return PixelVector(x, y);
}

void Screen::drawRect(const PixelRect& rect, const sf::Color& color)
{
	sf::RectangleShape s;
	s.setPosition(sf::Vector2f(rect.getPosition().getX(), rect.getPosition().getY()));
	s.setSize(sf::Vector2f(rect.getSize().getX(), rect.getSize().getY()));
	s.setFillColor(color);
	window->draw(s);
}

void Screen::drawImageID(const ImageID& id, const PixelRect& rect)
{
	Debug::warn("Screen::drawImageID(): TODO");
}

void Screen::drawImage(const sf::Image& image, const PixelRect& rect)
{
	sf::Texture tex;
	tex.update(image);
	sf::Sprite s(tex);
	s.move(rect.getPosition().getX(), rect.getPosition().getY());
	window->draw(s);
}

void Screen::drawText(const std::string& str, const PixelVector& position, const sf::Color& color)
{
	text.setString(str);
	text.setPosition(position.getX(), position.getY());
	text.setColor(color);
	window->draw(text);
}
