#include "Main.hpp"

#include <misc/Global.hpp>
#include "Screen.hpp"
#include <team/Team.hpp>
#include <avatar/LobbyAvatar.hpp>
#include <skill/LobbySkill.hpp>
#include <item/LobbyItem.hpp>
#include <graphics/GraphicsManager.hpp>
#include <misc/Account.hpp>
#include <network/NetworkDevice.hpp>
#include <menu/MenuList.hpp>

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
	LobbyAvatar::init();
	LobbySkill::init();
	LobbyItem::init();
	GraphicsManager::init();
	networkDevice = new NetworkDevice();
	menuList = new MenuList();
	run();
}

Main::~Main()
{
	deleteAndNULL(menuList);
	deleteAndNULL(networkDevice);
	Account::uninit();
	Screen::uninit();
	Team::uninit();
	LobbyAvatar::uninit();
	LobbySkill::uninit();
	LobbyItem::uninit();
	GraphicsManager::uninit();
}

NetworkDevice* Main::getNetworkDevice()
{
	return networkDevice;
}

void Main::run()
{
	sf::Clock clock;
	float time = 0.f;
	while (running)
	{
		time += clock.restart().asSeconds();
		if (time > 1.f/global::FPS)
		{
			time -= 1.f/global::FPS;
			tick();
			render();
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
