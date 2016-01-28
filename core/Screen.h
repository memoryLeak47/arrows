#ifndef __SCREEN_CLASS__
#define __SCREEN_CLASS__

#include <SFML/Graphics.hpp>
#include <string>

#include "Main.h"
#include "../math/pixel/PixelRect.h"
#include "../graphics/ImageID.h"

class Screen
{
	private:
		static sf::RenderWindow *window;
	public:
		static void init();
		static void uninit();
		static void tick();
		static void display();

		static void drawRect(const PixelRect&, const sf::Color&);
		static void drawImageID(const ImageID&, const PixelRect&);
		static void drawText(const std::string&, const PixelRect&, const sf::Color&);
};



#endif
