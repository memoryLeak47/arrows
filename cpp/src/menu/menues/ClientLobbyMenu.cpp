#include "ClientLobbyMenu.hpp"

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
	return NULL; // TODO
}

void ClientLobbyMenu::handlePacket(Packet* packet, const sf::IpAddress& ip)
{
	if (ip == serverIP)
	{
		handlePacketByID(packet, 0);
	}
	else
	{
		Debug::warn("got packet from strange ip...");
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

void ClientLobbyMenu::handleLoginUserPacket(LoginUserPacket* packet, int id)
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

void ClientLobbyMenu::handleLobbyPlayersPacket(LobbyPlayersPacket* packet, int id)
{
	std::vector<LobbyPlayer*> players(packet->getPlayers());
	for (int i = 0; i < players.size(); i++)
	{
		addPlayer(players[i]);
	}
	updatePlayerIcons();
}
