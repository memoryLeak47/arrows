#include "ClientLobbyMenu.hpp"

#include "../../misc/Converter.hpp"
#include "../../misc/Debug.hpp"
#include "../../core/Main.hpp"

ClientLobbyMenu::ClientLobbyMenu(const std::string& ip) : serverIP(ip)
{
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
		Debug::warn("ClientLobbyMenu::handlePacket(): awkward packet(" + Converter::intToString((int)packet->getCID()) + ") in awkward phase(" + Converter::intToString(getPhase()) + ")");
	}
}

void ClientLobbyMenu::lockPressed() {}

void ClientLobbyMenu::disconnectPressed()
{
	Main::getMenuList()->back();
}

void ClientLobbyMenu::teamPressed(Team* team) {}

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

void ClientLobbyMenu::handleLockUserPacket(LockUserPacket*, int)
{
	Debug::warn("ClientLobbyMenu::handleLockUserPacket(): should not be called, maybe forgotten to overwrite");
}

void ClientLobbyMenu::handleDisconnectUserPacket(DisconnectUserPacket*, int)
{
	Debug::warn("ClientLobbyMenu::handleDisconnectUserPacket(): should not be called, maybe forgotten to overwrite");
}

void ClientLobbyMenu::handleTeamUserPacket(TeamUserPacket*, int)
{
	Debug::warn("ClientLobbyMenu::handleTeamUserPacket(): should not be called, maybe forgotten to overwrite");
}

void ClientLobbyMenu::handleAvatarUserPacket(AvatarUserPacket*, int)
{
	Debug::warn("ClientLobbyMenu::handleAvatarUserPacket(): should not be called, maybe forgotten to overwrite");
}

void ClientLobbyMenu::handleSkillUserPacket(SkillUserPacket*, int)
{
	Debug::warn("ClientLobbyMenu::handleSkillUserPacket(): should not be called, maybe forgotten to overwrite");
}

void ClientLobbyMenu::handleItemUserPacket(ItemUserPacket*, int)
{
	Debug::warn("ClientLobbyMenu::handleItemUserPacket(): should not be called, maybe forgotten to overwrite");
}

void ClientLobbyMenu::handleMapPacket(MapPacket*)
{
	Debug::warn("ClientLobbyMenu::handleMapPacket(): should not be called, maybe forgotten to overwrite");
}
