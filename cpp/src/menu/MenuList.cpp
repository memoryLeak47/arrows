#include "MenuList.hpp"

#include <misc/Global.hpp>
#include "menues/LoginMenu.hpp"
#include <game/ServerGameInterface.hpp>
#include <core/Main.hpp>

MenuList::MenuList()
{
	if (global::SKIP_LOBBY)
	{
		LobbyTileMap* lobbyTileMap = new LobbyTileMap(LobbyTileMap::getIntsByFile("res/maps/" + global::SKIP_LOBBY_MAP));
		std::vector<LobbyPlayer*> lobbyPlayers;
		LobbyPlayer* player = new LobbyPlayer(new LoginUserPacket("myself", 42));
		player->applyTeamUserPacket(new TeamUserPacket((char)0));
		player->applyAvatarUserPacket(new AvatarUserPacket((char)0));
		std::string a = "";
		a += (char)0;
		a += (char)0;
		a += (char)0;
		player->applyItemUserPacket(new ItemUserPacket(a));
		a += (char)0;
		player->applySkillUserPacket(new SkillUserPacket(a));

		lobbyPlayers.push_back(player);
		menues.push_back(new ServerGameInterface(lobbyTileMap, lobbyPlayers));
	}
	else
	{
		menues.push_back(new LoginMenu());
	}
}

MenuList::~MenuList()
{
	deleteAndClearVector(menues);
}

void MenuList::onEvent(const sf::Event &event)
{
	if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Return)
	{
		getTopmostMenu()->tick();
	}
	else
	{
		getTopmostMenu()->onEvent(event);
	}
}

void MenuList::tick()
{
	if (!global::DEBUG_STEPWISE)
	{
		getTopmostMenu()->tick();
	}
}

void MenuList::render()
{
	for (unsigned int i = getTopmostFullscreenMenuIndex(); i < getMenues().size(); i++)
	// für alle menues die auf dem obersten fullscreen menu liegen (und dem obersten fullscreen-menu)
	{
		getMenues()[i]->render(); // render
	}
}

void MenuList::addMenu(Menu* menu)
{
	menues.push_back(menu);
}

void MenuList::back()
{
	deleteAndNULL(menues[menues.size()-1]);
	menues.pop_back();
}

std::vector<Menu*> MenuList::getMenues()
{
	return menues;
}

// bekomme oberstes menu
Menu* MenuList::getTopmostMenu()
{
	return menues.back();
}

// returne den index des obersten menues
int MenuList::getTopmostFullscreenMenuIndex()
{
	for (int i = getMenues().size()-1; i >= 0; i--) // für alle menues (von hinten nach vorne)
	{
		if (getMenues()[i]->isFullscreen()) // wenn du fullscreen bist
		{
			return i; // returne deinen index
		}
	} // wenn keins fullscreen ist
	Debug::error("MenuList.getTopmostFullscreenMenuIndex() no fullscreen menu!"); // beende das programm und schmeiß nen error
	return 0;
}

