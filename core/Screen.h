#ifndef __SCREEN_CLASS__
#define __SCREEN_CLASS__

#include <SFML/Graphics.hpp>

#include "Main.h"

class Screen
{
	private:
		static sf::RenderWindow *window;
	public:
		static void init();
		static void uninit();
		static void tick();
		static void display();
};



#endif
