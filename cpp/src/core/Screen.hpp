#ifndef __SCREEN_CLASS__
#define __SCREEN_CLASS__

class PixelVector;
class PixelRect;

#include <SFML/Graphics/Color.hpp>
#include <graphics/GraphicsID.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <string>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

class Screen
{
	public:
		static void init();
		static void uninit();
		static void tick();
		static void display();
		static PixelVector getCursorPosition();
		static PixelVector getSize();

		static void drawRect(const PixelRect&, const sf::Color&);
		static void fillRect(const PixelRect&, const sf::Color&);
		static void drawGraphicsID(const PixelRect&, GraphicsID, int index=0, float rotation=0);
		static void drawTexture(const sf::Texture*, const PixelRect&, float rotation=0);
		static void drawText(const std::string&, const PixelVector&, const sf::Color&);
		static void renderCursor();
	private:
		static PixelVector cursorPosition;
		static sf::RenderWindow *window;
		static sf::Text text;
};

#endif
