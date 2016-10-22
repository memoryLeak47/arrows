#include "ClientLobbyMenu.hpp"

#include <misc/Global.hpp>
#include <menu/MenuList.hpp>
#include <menu/components/Button.hpp>
#include <core/Main.hpp>
#include <game/ClientGameInterface.hpp>
#include <network/packets/LoginUserPacket.hpp>
#include <network/packets/SkillUserPacket.hpp>
#include <network/packets/AvatarUserPacket.hpp>
#include <network/packets/ItemUserPacket.hpp>
#include <network/packets/PlayerPropertyUserPacket.hpp>
#include <network/packets/MapPacket.hpp>
#include <network/packets/LobbyPlayersPacket.hpp>
#include <network/packets/TeamUserPacket.hpp>
#include <network/packets/DisconnectUserPacket.hpp>
#include <network/packets/LockUserPacket.hpp>
#include <network/packets/UserPacketWithID.hpp>
#include <tile/map/LobbyTileMap.hpp>
#include <player/LobbyPlayer.hpp>
#include <player/property/Team.hpp>

ClientLobbyMenu::ClientLobbyMenu(const std::string& ip)
	: localPlayerID(-1)
{
	serverIP = new sf::IpAddress(ip);
	LoginUserPacket* p = new LoginUserPacket(Main::getName(), Main::getRank());
	sendToServer(p);
	deleteAndNULL(p);
}

ClientLobbyMenu::~ClientLobbyMenu()
{
	delete serverIP;
}

LobbyPlayer* ClientLobbyMenu::getLocalPlayer() const
{
	return getPlayer(localPlayerID);
}

void ClientLobbyMenu::handlePacket(Packet* packet, sf::IpAddress* ip)
{
	if (packet == NULL) Debug::warn("ClientLobbyMenu::handlePacket(): packet == NULL");

	if ((*ip) == (*serverIP))
	{
		handlePacketByID(packet, 0);
	}
	else
	{
		Debug::warn("got packet from non-server player");
		deleteAndNULL(packet);
	}
}

void ClientLobbyMenu::handlePacketByID(Packet* packet, int id)
{
	if (packet->getCID() == USER_PACKET_WITH_ID_CID)
	{
		handlePacketByID(((UserPacketWithID*) packet)->getPacket(), ((UserPacketWithID*) packet)->getID());
	}
	else if (packet->getCID() == LOCK_USER_PACKET_CID)
	{
		handleLockUserPacket((LockUserPacket*) packet, id);
	}
	else if (packet->getCID() == DISCONNECT_USER_PACKET_CID)
	{
		handleDisconnectUserPacket((DisconnectUserPacket*) packet, id);
	}
	else if (packet->getCID() == TEAM_USER_PACKET_CID && getPhase() == TEAM_PHASE)
	{
		handleTeamUserPacket((TeamUserPacket*) packet, id);
	}
	else if (packet->getCID() == LOGIN_USER_PACKET_CID && getPhase() == TEAM_PHASE)
	{
		handleLoginUserPacket((LoginUserPacket*) packet);
	}
	else if (packet->getCID() == AVATAR_USER_PACKET_CID && getPhase() == AVATAR_PHASE)
	{
		handleAvatarUserPacket((AvatarUserPacket*) packet, id);
	}
	else if (packet->getCID() == SKILL_USER_PACKET_CID && getPhase() == SKILL_PHASE)
	{
		handleSkillUserPacket((SkillUserPacket*) packet, id);
	}
	else if (packet->getCID() == ITEM_USER_PACKET_CID && getPhase() == ITEM_PHASE)
	{
		handleItemUserPacket((ItemUserPacket*) packet, id);
	}
	else if (packet->getCID() == MAP_PACKET_CID && getPhase() == TEAM_PHASE)
	{
		handleMapPacket((MapPacket*) packet);
	}
	else if (packet->getCID() == LOBBY_PLAYERS_PACKET_CID)
	{
		handleLobbyPlayersPacket((LobbyPlayersPacket*) packet);
	}
	else
	{
		Debug::warn("ClientLobbyMenu::handlePacketByID(): awkward packet(" + Converter::intToString((int)packet->getCID()) + ") in awkward phase(" + Converter::intToString(getPhase()) + ")");
	}
	deleteAndNULL(packet);
}

void ClientLobbyMenu::lockPressed()
{
	if (getLocalPlayer() == NULL) Debug::warn("ClientLobbyMenu::lockPressed(): getLocalPlayer() == NULL");
	if (getLocalPlayer()->getLockUserPacket() == NULL) Debug::warn("ClientLobbyMenu::lockPressed(): getLocalPlayer()->getLockUserPacket() == NULL");
	LockUserPacket* packet = new LockUserPacket(!getLocalPlayer()->getLockUserPacket()->isLocked());
	sendToServer(packet);
	deleteAndNULL(packet);
}

void ClientLobbyMenu::disconnectPressed()
{
	DisconnectUserPacket* packet = new DisconnectUserPacket();
	sendToServer(packet);
	deleteAndNULL(packet);
	Main::getMenuList()->back();
}

void ClientLobbyMenu::teamPressed(Team* team)
{
	TeamUserPacket* packet = new TeamUserPacket(team->getID());
	sendToServer(packet);
	deleteAndNULL(packet);
}

void ClientLobbyMenu::sendToServer(Packet* p)
{
	send(p, serverIP);
}

void ClientLobbyMenu::handleLoginUserPacket(LoginUserPacket* packet)
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

	updatePlayerIcons();
}

void ClientLobbyMenu::handleLockUserPacket(LockUserPacket* packet, int id)
{
	if (id == 0)
	{
		nextPhase();
	}
	else
	{
		getPlayer(id)->applyLockUserPacket(packet);
	}
}

void ClientLobbyMenu::handleDisconnectUserPacket(DisconnectUserPacket* packet, int id)
{
	removePlayer(id);

	unlockAll();
	updatePlayerIcons();
}

void ClientLobbyMenu::handleTeamUserPacket(TeamUserPacket* packet, int id)
{
	getPlayer(id)->applyTeamUserPacket(packet);

	unlockAll();
	updatePlayerIcons();
}

void ClientLobbyMenu::handleAvatarUserPacket(AvatarUserPacket* packet, int id)
{
	LobbyPlayer* player = getPlayer(id);
	if (player == NULL) Debug::warn("ClientLobbyMenu::handleAvatarUserPacket(): getPlayer(" + Converter::intToString(id) + ") == NULL");
	player->applyAvatarUserPacket(packet);
}

void ClientLobbyMenu::handleSkillUserPacket(SkillUserPacket* packet, int id)
{
	LobbyPlayer* player = getPlayer(id);
	if (player == NULL) Debug::warn("ClientLobbyMenu::handleSkillUserPacket(): getPlayer(" + Converter::intToString(id) + ") == NULL");
	player->applySkillUserPacket(packet);
}

void ClientLobbyMenu::handleItemUserPacket(ItemUserPacket* packet, int id)
{

	LobbyPlayer* player = getPlayer(id);
	if (player == NULL) Debug::warn("ClientLobbyMenu::handleItemUserPacket(): getPlayer(" + Converter::intToString(id) + ") == NULL");
	player->applyItemUserPacket(packet);
}

void ClientLobbyMenu::handleMapPacket(MapPacket* packet)
{
	unlockAll();
	updateMap(packet->getInts());
}

void ClientLobbyMenu::updateLockButton() const
{
	switch (getPhase())
	{
		case TEAM_PHASE:
			lockButton->setEnabled(getLobbyTileMap()->isValid());
		break;
		case AVATAR_PHASE:
			lockButton->setEnabled(getLocalPlayer()->getAvatarUserPacket()->isValid());
		break;
		case SKILL_PHASE:
			lockButton->setEnabled(getLocalPlayer()->getSkillUserPacket()->isValid());
		break;
		case ITEM_PHASE:
			lockButton->setEnabled(getLocalPlayer()->getItemUserPacket()->isValid());
		break;
	}
}

void ClientLobbyMenu::playerPropertySelected(PlayerPropertyUserPacket* packet)
{
	switch (packet->getCID())
	{
		case AVATAR_USER_PACKET_CID:
			getLocalPlayer()->applyAvatarUserPacket(dynamic_cast<AvatarUserPacket*>(packet));
			break;
		case SKILL_USER_PACKET_CID:
			getLocalPlayer()->applySkillUserPacket(dynamic_cast<SkillUserPacket*>(packet));
			break;
		case ITEM_USER_PACKET_CID:
			getLocalPlayer()->applyItemUserPacket(dynamic_cast<ItemUserPacket*>(packet));
			break;
		default:
			Debug::warn("ClientLobbyMenu::playerPropertySelected(): awkward packet");
	}
	sendToServer(packet);
}

void ClientLobbyMenu::createGameInterface()
{
	Main::getMenuList()->addMenu(new ClientGameInterface(getLobbyTileMap(), getPlayers(), localPlayerID, serverIP));
}
