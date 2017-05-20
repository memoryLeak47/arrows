#include "ClientLobbyMenu.hpp"

#include <misc/Global.hpp>
#include <menu/MenuList.hpp>
#include <menu/components/Button.hpp>
#include <core/Main.hpp>
#include <game/ClientGameInterface.hpp>
#include <network/packets/LoginPacket.hpp>
#include <network/packets/SkillPacket.hpp>
#include <network/packets/AvatarPacket.hpp>
#include <network/packets/ItemPacket.hpp>
#include <network/packets/PlayerPropertyPacket.hpp>
#include <network/packets/MapPacket.hpp>
#include <network/packets/LobbyPlayersPacket.hpp>
#include <network/packets/TeamPacket.hpp>
#include <network/packets/DisconnectPacket.hpp>
#include <network/packets/LockPacket.hpp>
#include <network/packets/PacketWithID.hpp>
#include <network/packets/GameStartPacket.hpp>
#include <tilemap/LobbyTileMap.hpp>
#include <player/LobbyPlayer.hpp>
#include <team/Team.hpp>

ClientLobbyMenu::ClientLobbyMenu(const std::string& ip)
	: LobbyMenu("Lock"), localPlayerID(-1)
{
	serverIP = ip;
	LoginPacket* p = new LoginPacket(Main::getName(), Main::getRank());
	sendToServer(p);
	deleteAndNullptr(p);
}

ClientLobbyMenu::~ClientLobbyMenu()
{}

LobbyPlayer* ClientLobbyMenu::getLocalPlayer() const
{
	return getPlayer(localPlayerID);
}

void ClientLobbyMenu::handlePacket(Packet* packet, const sf::IpAddress& ip)
{
	if (packet == nullptr) Debug::warn("ClientLobbyMenu::handlePacket(): packet == nullptr");
	if (ip == serverIP)
	{
		handlePacketByID(packet, 0);
	}
	else
	{
		Debug::warn("got packet from non-server player");
		deleteAndNullptr(packet);
	}
}

void ClientLobbyMenu::handlePacketByID(Packet* packet, int id)
{
	if (packet->getCompressID() == CompressIDs::PACKET_WITH_ID)
	{
		PacketWithID* packetWithID = packet->unwrap<PacketWithID>();
		handlePacketByID(packetWithID->getPacket(), packetWithID->getID());
	}
	else if (packet->getCompressID() == CompressIDs::LOCK_PACKET)
	{
		handleLockPacket(packet->unwrap<LockPacket>(), id);
	}
	else if (packet->getCompressID() == CompressIDs::DISCONNECT_PACKET)
	{
		handleDisconnectPacket(packet->unwrap<DisconnectPacket>(), id);
	}
	else if (packet->getCompressID() == CompressIDs::TEAM_PACKET && getPhase() == TEAM_PHASE)
	{
		handleTeamPacket(packet->unwrap<TeamPacket>(), id);
	}
	else if (packet->getCompressID() == CompressIDs::LOGIN_PACKET && getPhase() == TEAM_PHASE)
	{
		handleLoginPacket(packet->unwrap<LoginPacket>());
	}
	else if (packet->getCompressID() == CompressIDs::AVATAR_PACKET && getPhase() == AVATAR_PHASE)
	{
		handleAvatarPacket(packet->unwrap<AvatarPacket>(), id);
	}
	else if (packet->getCompressID() == CompressIDs::SKILL_PACKET && getPhase() == SKILL_PHASE)
	{
		handleSkillPacket(packet->unwrap<SkillPacket>(), id);
	}
	else if (packet->getCompressID() == CompressIDs::ITEM_PACKET && getPhase() == ITEM_PHASE)
	{
		handleItemPacket(packet->unwrap<ItemPacket>(), id);
	}
	else if (packet->getCompressID() == CompressIDs::MAP_PACKET && getPhase() == TEAM_PHASE)
	{
		handleMapPacket(packet->unwrap<MapPacket>());
	}
	else if (packet->getCompressID() == CompressIDs::LOBBY_PLAYERS_PACKET)
	{
		handleLobbyPlayersPacket(packet->unwrap<LobbyPlayersPacket>());
	}
	else if (packet->getCompressID() == CompressIDs::GAME_START_PACKET)
	{
		handleGameStartPacket(packet->unwrap<GameStartPacket>());
	}
	else
	{
		Debug::warn("ClientLobbyMenu::handlePacketByID(): awkward packet(" + Converter::intToString((int) packet->getCompressID()) + ") in awkward phase(" + Converter::intToString(getPhase()) + ")");
	}
	deleteAndNullptr(packet);
}

void ClientLobbyMenu::lockPressed()
{
	// Error-Handling
	if (getLocalPlayer() == nullptr) Debug::warn("ClientLobbyMenu::lockPressed(): getLocalPlayer() == nullptr");
	if (getLocalPlayer()->getLockPacket() == nullptr) Debug::warn("ClientLobbyMenu::lockPressed(): getLocalPlayer()->getLockPacket() == nullptr");

	// send changed lock status to server (not applied here)
	LockPacket* packet = new LockPacket(!getLocalPlayer()->getLockPacket()->isLocked());
	sendToServer(packet);
	deleteAndNullptr(packet);
}

void ClientLobbyMenu::disconnectPressed()
{
	DisconnectPacket* packet = new DisconnectPacket();
	sendToServer(packet);
	deleteAndNullptr(packet);
	Main::getMenuList()->back();
}

void ClientLobbyMenu::teamPressed(Team* team)
{
	TeamPacket* packet = new TeamPacket(team->getID());
	sendToServer(packet);
	deleteAndNullptr(packet);
}

void ClientLobbyMenu::sendToServer(Packet* p)
{
	send(p, serverIP);
}

void ClientLobbyMenu::handleLoginPacket(LoginPacket* packet)
{
	LobbyPlayer* player = new LobbyPlayer(packet);
	addPlayer(player);
	if (localPlayerID == -1)
	{
		localPlayerID = getPlayers().size()-1;
	}

	unlockAll();
	updatePlayerIcons();
}

void ClientLobbyMenu::handleLobbyPlayersPacket(LobbyPlayersPacket* packet)
{
	clearPlayers();
	std::vector<LobbyPlayer*> players(packet->getPlayers());
	for (unsigned int i = 0; i < players.size(); i++)
	{
		addPlayer(players[i]);
	}

	if (global::AUTO_LOBBY)
	{
		switch (getPhase())
		{
			case AVATAR_PHASE:
			{
				playerPropertySelected(new AvatarPacket(global::AUTO_AVATAR));
				break;
			}
			case SKILL_PHASE:
			{
				playerPropertySelected(new SkillPacket(global::AUTO_SKILLS));
				break;
			}
			case ITEM_PHASE:
			{
				playerPropertySelected(new ItemPacket(global::AUTO_ITEMS));
				break;
			}
		}
	}

	updatePlayerIcons();
}

void ClientLobbyMenu::handleLockPacket(LockPacket* packet, int id)
{
	if (id == 0)
	{
		nextPhase();
	}
	else
	{
		getPlayer(id)->applyLockPacket(packet);
	}
}

void ClientLobbyMenu::handleDisconnectPacket(DisconnectPacket* packet, int id)
{
	removePlayer(id);

	unlockAll();
	updatePlayerIcons();
}

void ClientLobbyMenu::handleTeamPacket(TeamPacket* packet, int id)
{
	getPlayer(id)->applyTeamPacket(packet);

	unlockAll();
	updatePlayerIcons();
}

void ClientLobbyMenu::handleAvatarPacket(AvatarPacket* packet, int id)
{
	LobbyPlayer* player = getPlayer(id);
	if (player == nullptr) Debug::warn("ClientLobbyMenu::handleAvatarPacket(): getPlayer(" + Converter::intToString(id) + ") == nullptr");
	player->applyAvatarPacket(packet);
}

void ClientLobbyMenu::handleSkillPacket(SkillPacket* packet, int id)
{
	LobbyPlayer* player = getPlayer(id);
	if (player == nullptr) Debug::warn("ClientLobbyMenu::handleSkillPacket(): getPlayer(" + Converter::intToString(id) + ") == nullptr");
	player->applySkillPacket(packet);
}

void ClientLobbyMenu::handleItemPacket(ItemPacket* packet, int id)
{

	LobbyPlayer* player = getPlayer(id);
	if (player == nullptr) Debug::warn("ClientLobbyMenu::handleItemPacket(): getPlayer(" + Converter::intToString(id) + ") == nullptr");
	player->applyItemPacket(packet);
}

void ClientLobbyMenu::handleMapPacket(MapPacket* packet)
{
	unlockAll();
	updateMap(packet->getTileIDs());
}

void ClientLobbyMenu::handleGameStartPacket(GameStartPacket* packet)
{
	Main::getMenuList()->addMenu(new ClientGameInterface(getLobbyTileMap(), getPlayers(), localPlayerID, serverIP, packet->getUnixBeginTime()));
	resetLobby();
}

void ClientLobbyMenu::updateLockButton() const
{
	switch (getPhase())
	{
		case TEAM_PHASE:
			lockButton->setEnabled(getLobbyTileMap()->isValid());
		break;
		case AVATAR_PHASE:
			lockButton->setEnabled(getLocalPlayer()->getAvatarPacket()->isValid());
		break;
		case SKILL_PHASE:
			lockButton->setEnabled(getLocalPlayer()->getSkillPacket()->isValid());
		break;
		case ITEM_PHASE:
			lockButton->setEnabled(getLocalPlayer()->getItemPacket()->isValid());
		break;
	}
}

void ClientLobbyMenu::playerPropertySelected(PlayerPropertyPacket* packet)
{
	switch (packet->getCompressID())
	{
		case CompressIDs::AVATAR_PACKET:
			getLocalPlayer()->applyAvatarPacket(packet->unwrap<AvatarPacket>());
			break;
		case CompressIDs::SKILL_PACKET:
			getLocalPlayer()->applySkillPacket(packet->unwrap<SkillPacket>());
			break;
		case CompressIDs::ITEM_PACKET:
			getLocalPlayer()->applyItemPacket(packet->unwrap<ItemPacket>());
			break;
		default:
			Debug::warn("ClientLobbyMenu::playerPropertySelected(): awkward packet");
	}
	sendToServer(packet);
}
