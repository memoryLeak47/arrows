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
	// timer
	// END timer

	while (true)
	{
		networkDevice->receive();
	}
}
