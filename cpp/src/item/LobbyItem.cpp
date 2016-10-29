#include "LobbyItem.hpp"

#include <misc/Global.hpp>
#include <core/Main.hpp>
#include "lobby/LobbyHealthRing.hpp"
#include "game/HealthRing.hpp"
#include "ItemID.hpp"

std::vector<LobbyItem*> LobbyItem::items;

void LobbyItem::init()
{
	#define X(iid, lobbyname, gamename) items.push_back(new lobbyname());
	#define Y(iid, lobbyname, gamename) items.push_back(new lobbyname());
	#include "ItemID.list"
	#undef X
	#undef Y

	for (unsigned int i = 0; i < items.size(); i++)
	{
		items[i]->setID(i);
	}
}

void LobbyItem::uninit()
{
	deleteAndClearVector(items);
}

LobbyItem* LobbyItem::get(int id)
{
	if (id < 0 || id >= getAmount()) Debug::warn("LobbyItem::get(): id(" + Converter::intToString(id) + ") out of range");
	return items[id];
}

int LobbyItem::getAmount()
{
	return items.size();
}

const std::vector<LobbyItem*> LobbyItem::getAllLobbyItems()
{
	return items;
}

void LobbyItem::setID(char id)
{
	this->id = id;
}

char LobbyItem::getID() const
{
	return id;
}

int LobbyItem::getMassStat() const
{
	return 0;
}

float LobbyItem::getHealthStat() const
{
	return 0;
}

Item* LobbyItem::createGameItem() const
{
	switch (getID())
	{
		#define X(iid, lobbyname, gamename) case iid: return new gamename(ItemGivethrough {this});
		#define Y(iid, lobbyname, gamename) case iid: return new gamename(ItemGivethrough {this});
		#include "ItemID.list"
		#undef X
		#undef Y
		default:
		{
			Debug::error("LobbyItem::createGameItem(): nothing found here");
			return nullptr;
		}
	}
}
