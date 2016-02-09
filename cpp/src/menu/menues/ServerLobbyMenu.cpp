#include "ServerLobbyMenu.hpp"

#include "../../core/Main.hpp"
#include "../../core/Screen.hpp"
#include "../../misc/Debug.hpp"

ServerLobbyMenu::ServerLobbyMenu()
{
	addComponent(mapSelectEditField = new EditField(this, PixelRect(Screen::getSize().getX()-240, 250, 50, 20), "default"));

	// Map Select - Button
	class MapSelectButton : public Button
	{
		public:
			MapSelectButton(ServerLobbyMenu* c, const PixelRect& r, const std::string& s) : Button(c, r, s) {}
			virtual void onPress() override
			{
				dynamic_cast<ServerLobbyMenu*>(getParent())->mapSelected();
			}
	};
	addComponent(mapSelectButton = new MapSelectButton(this, PixelRect(Screen::getSize().getX()-180, 250, 50, 20), "Ok"));


	createServerPlayer();
	updatePlayerIcons();
}

void ServerLobbyMenu::mapSelected()
{
	std::string path = "res/maps/" + mapSelectEditField->getText() + ".png";
	std::vector<std::vector<int>> ints = LobbyTileMap::getIntsByFile(path);

	if (ints.size() == 0)
	{
		popup("can't load '" + path + "'");
		Debug::warn("ServerLobbyMenu::mapSelected(): ints.size() == 0");
		return;
	}

	updateMap(ints);

	// sendet neue Map zu allen Clients
	// TODO sendToAllClients(new MapPacket(ints));
	unlockAll();
}

void ServerLobbyMenu::handlePacket(Packet* packet, const sf::IpAddress& ip)
{
	handlePacketByID(packet, ipToID(ip, getPlayers()));
}

void ServerLobbyMenu::createServerPlayer()
{
	LobbyPlayer* me = new LobbyPlayer(new LoginUserPacket(Main::getAccount()->getName(), Main::getAccount()->getRank()));
	addPlayer(me);
}

void ServerLobbyMenu::lockPressed()
{
	LockUserPacket* l = new LockUserPacket(!getLocalPlayer()->getLockUserPacket()->isLocked());
	packAndSendToAllClients(l, 0);
	delete l;
	nextPhase();
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
	Debug::warnIf(getPlayers().size() == 0, "ServerLobbyMenu::getLocalPlayer(): getPlayers().size() == 0 -> is probably NULL");
	return getPlayer(0);
}

void ServerLobbyMenu::packAndSendToAllClients(UserPacket* p, int id) const
{
	for (int i = 1; i < getPlayers().size(); i++)
	{
		UserPacketWithID* packet = new UserPacketWithID(p, id);
		send(packet, getPlayer(i)->getIP());
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

LobbyPlayer* ServerLobbyMenu::getUpdatedPlayer(int id) const
{
	Debug::warnIf(id < 0 || id >= getUpdatedPlayers().size(), "ServerLobbyMenu::getUpdatedPlayers(): size == 0");
	return getUpdatedPlayers()[id];
}

std::vector<LobbyPlayer*> ServerLobbyMenu::getUpdatedPlayers() const
{
	return updatedPlayers;
}

void ServerLobbyMenu::addUpdatedPlayer(LobbyPlayer* p)
{
	updatedPlayers.push_back(p);
}

void ServerLobbyMenu::addPlayer(LobbyPlayer* p)
{
	LobbyMenu::addPlayer(p);
	addUpdatedPlayer(p);
}
