#include "ClientLobbyMenu.hpp"

#include "../../misc/Converter.hpp"
#include "../../misc/Debug.hpp"
#include "../../core/Main.hpp"

ClientLobbyMenu::ClientLobbyMenu(const std::string& ip) : serverIP(ip)
{
	localPlayer = NULL;
	LoginUserPacket* p = new LoginUserPacket(Main::getName(), Main::getRank());
	sendToServer(p);
	delete p;
}

LobbyPlayer* ClientLobbyMenu::getLocalPlayer() const
{
	Debug::warnIf(localPlayer == NULL, "ClientLobbyMenu::getLocalPlayer(): localPlayer == NULL");
	return localPlayer;
}

void ClientLobbyMenu::handlePacket(Packet* packet, const sf::IpAddress& ip)
{
	Debug::warnIf(packet == NULL, "ClientLobbyMenu::handlePacket(): packet == NULL");

	if (ip == serverIP)
	{
		handlePacketByID(packet, 0);
	}
	else
	{
		Debug::warn("got packet from non-server player");
		delete packet;
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
	else if (packet->getCID() == LOBBY_PLAYERS_PACKET_CID && getPhase() == TEAM_PHASE)
	{
		handleLobbyPlayersPacket((LobbyPlayersPacket*) packet);
	}
	else
	{
		Debug::warn("ClientLobbyMenu::handlePacketByID(): awkward packet(" + Converter::intToString((int)packet->getCID()) + ") in awkward phase(" + Converter::intToString(getPhase()) + ")");
	}
	delete packet;
}

void ClientLobbyMenu::lockPressed()
{
	Debug::warnIf(getLocalPlayer() == NULL, "ClientLobbyMenu::lockPressed(): getLocalPlayer() == NULL");
	Debug::warnIf(getLocalPlayer()->getLockUserPacket() == NULL, "ClientLobbyMenu::lockPressed(): getLocalPlayer()->getLockUserPacket() == NULL");
	LockUserPacket* packet = new LockUserPacket(!getLocalPlayer()->getLockUserPacket()->isLocked());
	sendToServer(packet);
	delete packet;
}

void ClientLobbyMenu::disconnectPressed()
{
	DisconnectUserPacket* packet = new DisconnectUserPacket();
	sendToServer(packet);
	delete packet;
	Main::getMenuList()->back();
}

void ClientLobbyMenu::teamPressed(Team* team)
{
	TeamUserPacket* packet = new TeamUserPacket(team->getID());
	sendToServer(packet);
	delete packet;
}

void ClientLobbyMenu::sendToServer(Packet* p)
{
	send(p, serverIP);
}

void ClientLobbyMenu::handleLoginUserPacket(LoginUserPacket* packet)
{
	LobbyPlayer* player = new LobbyPlayer(packet);
	addPlayer(player);
	if (localPlayer == NULL)
	{
		localPlayer = player;
	}

	unlockAll();
	updatePlayerIcons();
}

void ClientLobbyMenu::handleLobbyPlayersPacket(LobbyPlayersPacket* packet)
{
	std::vector<LobbyPlayer*> players(packet->getPlayers());
	for (int i = 0; i < players.size(); i++)
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
	Debug::warnIf(player == NULL, "ClientLobbyMenu::handleAvatarUserPacket(): getPlayer(" + Converter::intToString(id) + ") == NULL");
	player->applyAvatarUserPacket(packet);
}

void ClientLobbyMenu::handleSkillUserPacket(SkillUserPacket* packet, int id)
{
	LobbyPlayer* player = getPlayer(id);
	Debug::warnIf(player == NULL, "ClientLobbyMenu::handleSkillUserPacket(): getPlayer(" + Converter::intToString(id) + ") == NULL");
	player->applySkillUserPacket(packet);
}

void ClientLobbyMenu::handleItemUserPacket(ItemUserPacket* packet, int id)
{
	LobbyPlayer* player = getPlayer(id);
	Debug::warnIf(player == NULL, "ClientLobbyMenu::handleItemUserPacket(): getPlayer(" + Converter::intToString(id) + ") == NULL");
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
