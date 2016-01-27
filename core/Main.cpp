#include "Main.h"

Main::Main()
{
	Debug::init();
	Screen::init();
	menuList = new MenuList();
	networkDevice = new NetworkDevice();
}

void Main::run()
{
	if (fork() == 0)
	{
		while (true)
		{
			networkDevice->receive();
		}
	}
	else
	{
		sf::Clock clock;
		// TODO
	}
}
