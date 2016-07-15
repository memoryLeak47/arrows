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
	while (running)
	{
		if (clock.getElapsedTime().asSeconds() > 1/global::FPS)
		{
			tick();
			render();
			clock.restart();
		}
	}
}

void Main::tick()
{
	Debug::funcOn("Main::tick()");
	networkDevice->receive();
	Screen::tick();
	menuList->tick();
	Debug::funcOff("Main::tick()");
}

void Main::render()
{
	Debug::funcOn("Main::render()");
	menuList->render();
	Screen::renderCursor();
	Screen::display();
	Debug::funcOff("Main::render()");
}

void Main::exit()
{
	Debug::note("Exiting...");
	running = false; // in the next-frame -> destructor
}

void Main::setAccount(Account* a)
{
	account = a;
}

Account* Main::getAccount()
{
	if (account == NULL) Debug::warn("Main::getAccount(): account == NULL");
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

bool Main::isRunning()
{
	return running;
}
