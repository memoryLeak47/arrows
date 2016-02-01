#include "Main.hpp"

#include "../misc/Debug.hpp"
#include "Screen.hpp"

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
	delete menuList;
	delete networkDevice;
	delete game;
	delete account; // really needed?
	Screen::uninit();
}

NetworkDevice* Main::getNetworkDevice()
{
	return networkDevice;
}

void Main::run()
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

void Main::tick()
{
	networkDevice->receive();
	Screen::tick();
	menuList->tick();
}

void Main::render()
{
	menuList->render();
	Screen::display();
}

void Main::exit()
{
	running = false; // in the next-frame -> destructor
	Debug::note("Exiting...");
}

void Main::setAccount(Account* a)
{
	account = a;
}

Account* Main::getAccount()
{
	Debug::warnIf(account == NULL, "Main::getAccount(): accounts == NULL");
	return account;
}

void Main::logout()
{
	delete account;
	account = NULL;
}

MenuList* Main::getMenuList()
{
	return menuList;
}
