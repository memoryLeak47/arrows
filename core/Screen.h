#ifndef __SCREEN_CLASS__
#define __SCREEN_CLASS__

#include <SFML/Graphics.hpp>

class Screen
{
	private:
		static sf::RenderWindow *window;
	public:
		static void init();
		static void uninit();
};



#endif
