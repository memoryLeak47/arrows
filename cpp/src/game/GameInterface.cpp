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
	: mainFrame(new Frame(map, lobbyPlayers)), startTime(startTime_arg)
{
	Debug::note("------------ [ GAME ON ] ------------");
	tileMap = mainFrame->tileMap;

	mainFrame->idlers.push_back(new TestKiste(GameVector(7.5f, 4.5f)));
	mainFrame->idlers.push_back(new TestKiste(GameVector(7.5f, 3.5f)));

	history.add(mainFrame->clone());
}

GameInterface::~GameInterface()
{
	delete tileMap;
	delete mainFrame;
}

void GameInterface::tick()
{
	if (startTime > global::unix_millis())
	{
		return;
	}

	if (getFrameCounter() % 50 == 0)
	{
		system("paplay /usr/share/sounds/ubuntu/notifications/Blip.ogg &");
	}

	historian.updateIfReady(&mainFrame, &history);
	subTick();
	history.add(mainFrame->clone());

	view.setSpot(getLocalPlayer()->getPosition());

	Debug::tickConsole();
	Menu::tick();
}

int GameInterface::ipToID(const sf::IpAddress& ip) const
{
	if (ip == sf::IpAddress::None)
	{
		Debug::error("GameInterface::ipToID(): ip is none");
	}

	for (unsigned int i = 0; i < mainFrame->players.size(); i++)
	{
		if (mainFrame->players[i]->getIP() == sf::IpAddress::None)
		{
			Debug::error("GameInterface::ipToID(): ip of player(" + Converter::intToString(i) + ") is none");
		}

		if (mainFrame->players[i] == getLocalPlayer())
			continue;

		if (mainFrame->players[i]->getIP() == ip)
		{
			return i;
		}
	}
	Debug::error("GameInterface::ipToID(): failed");
	return -1;
}

GamePlayer* GameInterface::getLocalPlayer() const
{
	return mainFrame->players[getLocalPlayerID()];
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
	for (unsigned int i = 0; i < mainFrame->players.size(); i++)
	{
		mainFrame->players[i]->renderBar(getView());
	}

	for (unsigned int i = 0; i < mainFrame->mobs.size(); i++)
	{
		mainFrame->mobs[i]->renderBar(getView());
	}
}

void GameInterface::renderEntities() const
{
	for (unsigned int i = 0; i < mainFrame->players.size(); i++)
	{
		mainFrame->players[i]->render(getView());
	}
	for (unsigned int i = 0; i < mainFrame->idlers.size(); i++)
	{
		mainFrame->idlers[i]->render(getView());
	}
	for (unsigned int i = 0; i < mainFrame->mobs.size(); i++)
	{
		mainFrame->mobs[i]->render(getView());
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

void GameInterface::addForeignCalendarEntry(int frameIndex, char playerID, Actions actions)
{
	historian.addCalendarEntry(frameIndex, playerID, actions, &history);
}

void GameInterface::addOwnCalendarEntry(int frameIndex, Actions actions)
{
	historian.addCalendarEntry(frameIndex, getLocalPlayerID(), actions, &history);
}

void GameInterface::backtrackIfNecessary()
{
	historian.backtrack(&history);
}

int GameInterface::getFrameCounter() const
{
	return history.getFrameCounter();
}

void GameInterface::applyCalendar()
{
	mainFrame->applyEntries(historian.getCalendarEntries(getFrameCounter()));
}

const View& GameInterface::getView() const
{
	return view;
}
