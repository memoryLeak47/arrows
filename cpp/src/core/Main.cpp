#include "Main.hpp"

#include "../misc/Debug.hpp"
#include "Screen.hpp"
#include "../player/property/Team.hpp"
#include "../player/property/avatar/Avatar.hpp"
#include "../player/property/skill/Skill.hpp"
#include "../player/property/item/Item.hpp"
#include "../graphics/GraphicsManager.hpp"

bool Main::running = true;
MenuList* Main::menuList;
NetworkDevice* Main::networkDevice;
Account* Main::account;

Main::Main()
{
	running = true;
	global::init();
	Debug::init();
	Account::init();
	Screen::init();
	Team::init();
	Avatar::init();
	Skill::init();
	Item::init();
	GraphicsManager::init();
	menuList = new MenuList();
	networkDevice = new NetworkDevice();
	run();
}

Main::~Main()
{
	deleteAndNULL(menuList);
	deleteAndNULL(networkDevice);
	Account::uninit();
	Screen::uninit();
	Team::uninit();
	Avatar::uninit();
	Skill::uninit();
	Item::uninit();
	GraphicsManager::uninit();
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

		if (tickCounter > global::MAX_TICK_COUNTER)
		{
			tick();
			tickCounter -= global::MAX_TICK_COUNTER;
		}
		if (renderCounter > global::MAX_RENDER_COUNTER)
		{
			render();
			renderCounter -= global::MAX_RENDER_COUNTER;
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
	Debug::warnIf(account == NULL, "Main::getAccount(): account == NULL");
	return account;
}

void Main::logout()
{
	account = NULL;
}

MenuList* Main::getMenuList()
{
	return menuList;
}

std::string Main::getName()
{
	return getAccount()->getName();
}

int Main::getRank()
{
	return getAccount()->getRank();
}
