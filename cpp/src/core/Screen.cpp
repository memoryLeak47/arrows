#include "Screen.hpp"

#include <algorithm>

#include "../misc/Global.hpp"
#include "Main.hpp"

PixelVector Screen::cursorPosition = PixelVector(0, 0);
sf::RenderWindow* Screen::window;
sf::Text Screen::text;

void Screen::init()
{
	window = new sf::RenderWindow(sf::VideoMode(getSize().x, getSize().y), "Arrows", global::WINDOW_STYLE);
	window->setMouseCursorVisible(false);
	sf::Mouse::setPosition(sf::Vector2i(getSize().x/2, getSize().y/2));
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
	deleteAndNULL(window);
}

void Screen::tick()
{
	static sf::Event event;
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			Main::exit();
		}
		else if (event.type == sf::Event::MouseMoved)
		{
			if (sf::Mouse::getPosition(*window).x != getSize().x/2 or sf::Mouse::getPosition(*window).y != getSize().y/2)
			{
				cursorPosition = cursorPosition + PixelVector(event.mouseMove.x - getSize().x/2, event.mouseMove.y - getSize().y/2);
				cursorPosition = PixelVector(
					std::min(std::max(cursorPosition.x, 0), getSize().x),
					std::min(std::max(cursorPosition.y, 0), getSize().y)
				);
				sf::Mouse::setPosition(sf::Vector2i(getSize().x/2, getSize().y/2), *window);
			}
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
	return cursorPosition;
}

PixelVector Screen::getSize()
{
	static PixelVector v(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);
	return v;
}

void Screen::drawRect(const PixelRect& rect, const sf::Color& color)
{
	sf::RectangleShape s;
	s.setPosition(sf::Vector2f(rect.getPosition().x, rect.getPosition().y));
	s.setSize(sf::Vector2f(rect.getSize().x, rect.getSize().y));

	s.setFillColor(sf::Color::Transparent);
	s.setOutlineColor(color);
	s.setOutlineThickness(2);
	window->draw(s);
}

void Screen::fillRect(const PixelRect& rect, const sf::Color& color)
{
	sf::RectangleShape s;
	s.setPosition(sf::Vector2f(rect.getPosition().x, rect.getPosition().y));
	s.setSize(sf::Vector2f(rect.getSize().x, rect.getSize().y));
	s.setFillColor(color);
	window->draw(s);
}

void Screen::drawGraphicsID(const PixelRect& rect, GraphicsID id, int index, float rotation)
{
	drawTexture(GraphicsManager::getTexture(id, index), rect, rotation);
}

void Screen::renderCursor()
{
	fillRect(PixelRect(cursorPosition - PixelVector(2,2), PixelVector(4,4)), sf::Color::White);
}

void Screen::drawTexture(const sf::Texture* tex, const PixelRect& rect, float rotation)
{
	sf::Sprite s(*tex);
	s.move(rect.getPosition().x, rect.getPosition().y);
	if (rotation != 0)
	{
		s.rotate(rotation);
	}
	s.setScale( ((float) rect.getSize().x)/tex->getSize().x, ((float) rect.getSize().y)/tex->getSize().y);
	window->draw(s);
}

void Screen::drawText(const std::string& str, const PixelVector& position, const sf::Color& color)
{
	text.setString(str);
	text.setPosition(position.x, position.y);
	text.setColor(color);
	window->draw(text);
}
