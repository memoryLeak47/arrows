#ifndef __SCREEN_CLASS__
#define __SCREEN_CLASS__

#include <string>
#include <SFML/Graphics.hpp>

class PixelRect;
class PixelVector;
class ImageID;

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
		static void drawImageID(const ImageID&, const PixelRect&);
		static void drawImage(const sf::Image&, const PixelRect&);
		static void drawText(const std::string&, const PixelVector&, const sf::Color&);
	private:
		static sf::RenderWindow *window;
		static sf::Text text;
};

#include "../math/pixel/PixelRect.hpp"
#include "../math/pixel/PixelVector.hpp"
#include "../graphics/ImageID.hpp"

#endif
