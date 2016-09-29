#ifndef __SCREEN_CLASS__
#define __SCREEN_CLASS__

#include <string>
#include <SFML/Graphics.hpp>

#include <graphics/GraphicsManager.hpp> // for the TextureID typedef

class PixelRect;
class PixelVector;

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

#include <math/pixel/PixelRect.hpp>
#include <math/pixel/PixelVector.hpp>

#endif
