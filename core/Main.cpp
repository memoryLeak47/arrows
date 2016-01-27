#include "Main.h"

bool Main::running = true;
MenuList* Main::menuList;
NetworkDevice* Main::networkDevice;
Game* Main::game;
Account* Main::account;

Main::Main()
{
	Debug::init();
	Screen::init();
	menuList = new MenuList();
	networkDevice = new NetworkDevice();
	running = true;
	run();
}

Main::~Main()
{
	exit();
}

void Main::run()
{
	if (fork() == 0)
	{
		while (running)
		{
			networkDevice->receive();
		}
	}
	else
	{
		sf::Clock clock;
		int renderCounter = 0;
		int tickCounter = 0;
		while (running)
		{
			int tmp = clock.getElapsedTime().asMilliseconds();
			renderCounter += tmp;
			tickCounter += tmp;

			if (tickCounter > MAX_TICK_COUNTER)
			{
				tick();
				tickCounter -= MAX_TICK_COUNTER;
			}
			if (renderCounter > MAX_RENDER_COUNTER)
			{
				render();
				renderCounter -= MAX_RENDER_COUNTER;
			}
		}
	}
}

void Main::tick()
{
	Screen::tick();
}

void Main::render()
{
	Screen::render();
}

void Main::exit()
{
	running = false;
	delete menuList;
	delete networkDevice;
	delete game;
	delete account; // really needed?
	Screen::uninit();
}
