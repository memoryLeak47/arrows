#include "ServerLobbyMenu.hpp"

#include "../../core/Main.hpp"

ServerLobbyMenu::ServerLobbyMenu()
{
	createServerPlayer();
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
	return getPlayers()[0];
}

void ServerLobbyMenu::packAndSendToAllClients(UserPacket* p, int id) const
{
	for (int i = 0; i < getPlayers().size(); i++)
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
