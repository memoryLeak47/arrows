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
#include <SFML/System.hpp>

bool Main::running = true;
MenuList* Main::menuList;
NetworkDevice* Main::networkDevice;
Account* Main::account;
int Main::frameCounter = 0;

Main::Main()
{
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
	deleteAndNullptr(menuList);
	deleteAndNullptr(networkDevice);
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
	const long int frame_time_micros = (long int) (1000000.f / global::FPS);
	long int first_frame_unix_micros;

	{
		const long int pre_begin_micros = global::unix_micros();
		first_frame_unix_micros = pre_begin_micros - (pre_begin_micros % frame_time_micros) + frame_time_micros;
		sf::sleep(sf::microseconds(first_frame_unix_micros - pre_begin_micros));
	}

	while (running)
	{
		const long int current_time = global::unix_micros();
		if (frameCounter * frame_time_micros + first_frame_unix_micros > current_time)
		{
			sf::sleep(sf::microseconds(frameCounter * frame_time_micros + first_frame_unix_micros - current_time));
		}
		else
		{
			Debug::warn("frame overload");
		}

		tick();
		render();
		frameCounter++;
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
	if (account == nullptr) Debug::warn("Main::getAccount(): account == nullptr");
	return account;
}

void Main::logout()
{
	account = nullptr;
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
