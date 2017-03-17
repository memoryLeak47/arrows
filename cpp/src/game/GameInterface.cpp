#include "GameInterface.hpp"

#include <core/Main.hpp>
#include <misc/Global.hpp>
#include <player/GamePlayer.hpp>
#include <player/LobbyPlayer.hpp>
#include <collision/CollisionDetector.hpp>
#include <collision/CollisionTester.hpp>
#include <collision/PhysicsHandler.hpp>
#include <avatar/LobbyAvatar.hpp>
#include <tilemap/GameTileMap.hpp>
#include <collision/CollisionEvent.hpp>
#include <entity/Tile.hpp>
#include <math/game/GameRect.hpp>

#include <network/packets/TeamPacket.hpp>
#include <network/packets/LoginPacket.hpp>
#include <network/packets/AvatarPacket.hpp>
#include <network/packets/SkillPacket.hpp>
#include <network/packets/ItemPacket.hpp>

#include <entity/TestKiste.hpp>

GameInterface::GameInterface(LobbyTileMap* map, const std::vector<LobbyPlayer*>& lobbyPlayers, long int startTime_arg)
	: frameCounter(0), startTime(startTime_arg), restrictedGameInterface(this), mainFrame(map, lobbyPlayers, &restrictedGameInterface), history(global::FRAME_HISTORY_SIZE)
{
	Debug::note("------------ [ GAME ON ] ------------");
	tileMap = mainFrame.tileMap;

	mainFrame.idlers.push_back(new TestKiste(GameVector(7.5f, 4.5f)));
	mainFrame.idlers.push_back(new TestKiste(GameVector(7.5f, 3.5f)));
}

GameInterface::~GameInterface()
{
	delete tileMap;
}

void GameInterface::tick()
{
	history.add(mainFrame.clone());

	if (frameCounter++ % 100 == 0)
	{
		system("paplay /usr/share/sounds/ubuntu/notifications/Blip.ogg &");
	}

	struct X {
		X(GameInterface* gi)
		{
			gi->view.setEntity(gi->getLocalPlayer());
			gi->view.changeFocus();
		}
	};
	static X x(this);

	Debug::tickConsole();
	Menu::tick();
}

int GameInterface::ipToID(const sf::IpAddress& ip) const
{
	if (ip == nullptr)
	{
		Debug::error("GameInterface::ipToID(): ip == nullptr");
	}

	for (unsigned int i = 0; i < mainFrame.players.size(); i++)
	{
		if (mainFrame.players[i]->getIP() == nullptr)
		{
			Debug::error("GameInterface::ipToID(): ip of player(" + Converter::intToString(i) + ") is nullptr");
		}

		if (mainFrame.players[i] == getLocalPlayer())
			continue;

		if (mainFrame.players[i]->getIP() == ip)
		{
			return i;
		}
	}
	Debug::error("GameInterface::ipToID(): failed");
	return -1;
}


void GameInterface::applyCalendar()
{
	std::vector<Calendar::Entry> entries = calendar.getEntries(frameCounter);
	for (auto i = entries.begin(); i != entries.end(); i++)
	{
		Calendar::Entry entry = *i;
		mainFrame.players[entry.playerID]->setActions(entry.actions);
	}
}

void GameInterface::render() const
{
	if (startTime > global::unix_millis())
	{
		return;
	}
	renderMap();
	renderBars();
	renderEntities();
	Menu::render();
	Debug::renderConsole();
}

void GameInterface::renderMap() const
{
	getGameTileMap()->render(getView());
}

void GameInterface::renderBars() const
{
	for (unsigned int i = 0; i < mainFrame.players.size(); i++)
	{
		mainFrame.players[i]->renderBar(getView());
	}

	for (unsigned int i = 0; i < mainFrame.mobs.size(); i++)
	{
		mainFrame.mobs[i]->renderBar(getView());
	}
}

void GameInterface::renderEntities() const
{
	for (unsigned int i = 0; i < mainFrame.players.size(); i++)
	{
		mainFrame.players[i]->render(getView());
	}
	for (unsigned int i = 0; i < mainFrame.idlers.size(); i++)
	{
		mainFrame.idlers[i]->render(getView());
	}
	for (unsigned int i = 0; i < mainFrame.mobs.size(); i++)
	{
		mainFrame.mobs[i]->render(getView());
	}
}

GameTileMap* GameInterface::getGameTileMap() const
{
	return tileMap;
}

Actions GameInterface::calcActions() const
{
	Actions actions;
	// movement
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		setAction(&actions, GO_LEFT, true);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		setAction(&actions, GO_RIGHT, true);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		setAction(&actions, JUMP, true);
	}

	// skills
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		setAction(&actions, SKILL0, true);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		setAction(&actions, SKILL1, true);
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		setAction(&actions, SKILL2, true);
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
	{
		setAction(&actions, SKILL3, true);
	}
	return actions;
}

const View& GameInterface::getView() const
{
	return view;
}
