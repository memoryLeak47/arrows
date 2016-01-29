#ifndef __SCREEN_CLASS__
#define __SCREEN_CLASS__

#include <SFML/Graphics.hpp>
#include <string>

class PixelRect;
class PixelVector;
class ImageID;

class Screen
{
	private:
		static sf::RenderWindow *window;
		static sf::Text text;
	public:
		static void init();
		static void uninit();
		static void tick();
		static void display();
		static const PixelVector& getCursorPosition();

		static void drawRect(const PixelRect&, const sf::Color&);
		static void drawImageID(const ImageID&, const PixelRect&);
		static void drawText(const std::string&, const PixelVector&, const sf::Color&);
};

#include "../math/pixel/PixelRect.h"
#include "../math/pixel/PixelVector.h"
#include "../graphics/ImageID.h"

#endif
