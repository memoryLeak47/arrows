#include "ServerLobbyMenu.hpp"

#include "../../core/Main.hpp"
#include "../../core/Screen.hpp"
#include "../../misc/Converter.hpp"
#include "../../misc/Debug.hpp"
//#include "../../network/packets/MapPacket.hpp"

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
	MapPacket* mapPacket = new MapPacket(ints);
	sendToAllClients(mapPacket);
	delete mapPacket;

	unlockAll();
}

void ServerLobbyMenu::handlePacket(Packet* packet, const sf::IpAddress& ip)
{
	if (packet->getCID() == LOCK_USER_PACKET_CID)
	{
		handleLockUserPacket((LockUserPacket*) packet, ipToID(ip, getPlayers()));
	}
	else if (packet->getCID() == DISCONNECT_USER_PACKET_CID)
	{
		handleDisconnectUserPacket((DisconnectUserPacket*) packet, ipToID(ip, getPlayers()));
	}
	else if (packet->getCID() == TEAM_USER_PACKET_CID && getPhase() == TEAM_PHASE)
	{
		handleTeamUserPacket((TeamUserPacket*) packet, ipToID(ip, getPlayers()));
	}
	else if (packet->getCID() == LOGIN_USER_PACKET_CID && getPhase() == TEAM_PHASE)
	{
		handleLoginUserPacket((LoginUserPacket*) packet, ip);
	}
	else if (packet->getCID() == AVATAR_USER_PACKET_CID && getPhase() == AVATAR_PHASE)
	{
		handleAvatarUserPacket((AvatarUserPacket*) packet, ipToID(ip, getPlayers()));
	}
	else if (packet->getCID() == SKILL_USER_PACKET_CID && getPhase() == SKILL_PHASE)
	{
		handleSkillUserPacket((SkillUserPacket*) packet, ipToID(ip, getPlayers()));
	}
	else if (packet->getCID() == ITEM_USER_PACKET_CID && getPhase() == ITEM_PHASE)
	{
		handleItemUserPacket((ItemUserPacket*) packet, ipToID(ip, getPlayers()));
	}
	else
	{
		Debug::warn("ServerLobbyMenu::handlePacket(): awkward packet(" + Converter::intToString((int)packet->getCID()) + ") in awkward phase(" + Converter::intToString(getPhase()) + ")");
	}
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
	TeamUserPacket* packet = new TeamUserPacket(team->getID());
	getLocalPlayer()->applyTeamUserPacket(packet);
	packAndSendToAllClients(packet, 0);
	updatePlayerIcons();
}

LobbyPlayer* ServerLobbyMenu::getLocalPlayer() const
{
	Debug::warnIf(getPlayers().size() == 0, "ServerLobbyMenu::getLocalPlayer(): getPlayers().size() == 0 -> is probably NULL");
	return getPlayer(0);
}

void ServerLobbyMenu::packAndSendToAllClients(UserPacket* p, int id) const
{
	UserPacketWithID* packet = new UserPacketWithID(p, id);
	for (int i = 1; i < getPlayers().size(); i++)
	{
		send(packet, getPlayer(i)->getIP());
	}
	delete packet;
}

void ServerLobbyMenu::sendToAllClients(Packet* packet) const
{
	for (int i = 1; i < getPlayers().size(); i++)
	{
		send(packet, getPlayer(i)->getIP());
	}
}

void ServerLobbyMenu::handleLockUserPacket(LockUserPacket* packet, int id)
{
	getPlayer(id)->applyLockUserPacket(packet);
	packAndSendToAllClients(packet, id);
}

void ServerLobbyMenu::handleDisconnectUserPacket(DisconnectUserPacket* packet, int id)
{
	getPlayers().erase(getPlayers().begin()+id);
	packAndSendToAllClients(packet, id);
}

void ServerLobbyMenu::handleTeamUserPacket(TeamUserPacket* packet, int id)
{
	getPlayer(id)->applyTeamUserPacket(packet);
	packAndSendToAllClients(packet, id);
	updatePlayerIcons();
}

void ServerLobbyMenu::handleLoginUserPacket(LoginUserPacket* packet, const sf::IpAddress& ip)
{
	if (ipToID(ip, getPlayers()) == -1) // Wenn es noch keinen Spieler mit dieser IP gibt
	{
		LobbyPlayer* player = new LobbyPlayer(packet, ip);
		Debug::noteIf(TAG_STATUS, "ServerLobbyMenu.handleLoginUserPacket(): Player \"" + player->getLoginUserPacket()->getName() + "\" joined the Game and is happy :)");
		LobbyPlayersPacket* playersPacket = new LobbyPlayersPacket(getPlayers()); // 
		send(playersPacket, ip); // liste ohne den Neuen an den Neuen senden.
		if (getLobbyTileMap()->isValid())
		{
			MapPacket* mapPacket = new MapPacket(getLobbyTileMap()->getInts());
			send(mapPacket, ip); // Die Map des neuen wird gesetzt
			delete mapPacket;
		}
		addPlayer(player);
		packAndSendToAllClients(packet, ipToID(ip, getPlayers())); // das erhaltene packet wird an alle clients weitergegeben
		updatePlayerIcons();
	}
	else
	{
		Debug::warn("ServerLobbyMenu.handleLoginUserPacket(): Spieler wollte ein zweites mal joinen");
	}
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

void ServerLobbyMenu::updateLockButton() const
{
	switch (getPhase())
	{
		case TEAM_PHASE:
			lockButton->setEnabled(areAllClientsLocked() && getLobbyTileMap()->isValid());
		break;
		case AVATAR_PHASE:
			lockButton->setEnabled(areAllClientsLocked() && getLocalPlayer()->getAvatarUserPacket()->isValid());
		break;
		case SKILL_PHASE:
			lockButton->setEnabled(areAllClientsLocked() && getLocalPlayer()->getSkillUserPacket()->isValid());
		break;
		case ITEM_PHASE:
			lockButton->setEnabled(areAllClientsLocked() && getLocalPlayer()->getItemUserPacket()->isValid());
		break;
	}
}
