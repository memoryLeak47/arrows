#include "ServerLobbyMenu.hpp"

#include "../../core/Main.hpp"
#include "../../misc/Debug.hpp"

ServerLobbyMenu::ServerLobbyMenu()
{
	createServerPlayer();
}

void ServerLobbyMenu::handlePacket(Packet* packet, const sf::IpAddress& ip)
{
	handlePacketByID(packet, ipToID(ip, getPlayers()));
}

void ServerLobbyMenu::createServerPlayer()
{
	LobbyPlayer* me = new LobbyPlayer(new LoginUserPacket(Main::getAccount()->getName(), Main::getAccount()->getRank()));
	updatedPlayers.push_back(me);
	getPlayers().push_back(me);
}

void ServerLobbyMenu::lockPressed()
{
	LockUserPacket* l = new LockUserPacket(!getLocalPlayer()->getLockUserPacket()->isLocked());
	packAndSendToAllClients(l, 0);
	delete l;
}

void ServerLobbyMenu::disconnectPressed()
{
	DisconnectUserPacket* dis = new DisconnectUserPacket();
	packAndSendToAllClients(dis, 0);
	delete dis;
	Main::getMenuList()->back();
}

void ServerLobbyMenu::teamPressed(Team* team)
{
	
}

LobbyPlayer* ServerLobbyMenu::getLocalPlayer() const
{
	Debug::warnIf(getPlayers().size() == 0, "ServerLobbyMenu::getLocalPlayer() getPlayers().size() == 0 -> is probably NULL");
	return getPlayers()[0];
}

void ServerLobbyMenu::packAndSendToAllClients(UserPacket* p, int id) const
{
	for (int i = 1; i < getPlayers().size(); i++)
	{
		UserPacketWithID* packet = new UserPacketWithID(p, id);
		send(packet, getPlayers()[i]->getIP());
		delete packet;
	}
}

void ServerLobbyMenu::handleLockUserPacket(LockUserPacket*, int)
{
}

void ServerLobbyMenu::handleDisconnectUserPacket(DisconnectUserPacket*, int)
{
}

void ServerLobbyMenu::handleTeamUserPacket(TeamUserPacket*, int)
{
}

void ServerLobbyMenu::handleLoginUserPacket(LoginUserPacket*, int)
{
}

void ServerLobbyMenu::handleAvatarUserPacket(AvatarUserPacket*, int)
{
}

void ServerLobbyMenu::handleSkillUserPacket(SkillUserPacket*, int)
{
}

void ServerLobbyMenu::handleItemUserPacket(ItemUserPacket*, int)
{
}
