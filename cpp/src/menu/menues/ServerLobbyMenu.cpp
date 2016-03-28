#include "ServerLobbyMenu.hpp"

#include "../../core/Main.hpp"
#include "../../core/Screen.hpp"
#include "../../misc/Converter.hpp"
#include "../../misc/Debug.hpp"
#include "../../game/ServerGameInterface.hpp"

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

ServerLobbyMenu::~ServerLobbyMenu()
{
	deleteAndClearVector(updatedPlayers);
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
	deleteAndNULL(mapPacket);

	unlockAll();
}

void ServerLobbyMenu::handlePacket(Packet* packet, sf::IpAddress* ip)
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
	deleteAndNULL(packet);
}

void ServerLobbyMenu::createServerPlayer()
{
	LoginUserPacket* packet = new LoginUserPacket(Main::getAccount()->getName(), Main::getAccount()->getRank());
	LobbyPlayer* me = new LobbyPlayer(packet);
	addPlayer(me);
	addUpdatedPlayer(me);
	deleteAndNULL(me);
	deleteAndNULL(packet);
}

void ServerLobbyMenu::lockPressed()
{
	LockUserPacket* l = new LockUserPacket(!getLocalPlayer()->getLockUserPacket()->isLocked());
	packAndSendToAllClients(l, 0);
	deleteAndNULL(l);
	nextPhase();
}

void ServerLobbyMenu::disconnectPressed()
{
	DisconnectUserPacket* dis = new DisconnectUserPacket();
	packAndSendToAllClients(dis, 0);
	deleteAndNULL(dis);
	Main::getMenuList()->back();
}

void ServerLobbyMenu::teamPressed(Team* team)
{
	TeamUserPacket* packet = new TeamUserPacket(team->getID());
	getLocalPlayer()->applyTeamUserPacket(packet);
	getUpdatedLocalPlayer()->applyTeamUserPacket(packet);
	packAndSendToAllClients(packet, 0);
	deleteAndNULL(packet);

	unlockAll();
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
	deleteAndNULL(packet);
}

void ServerLobbyMenu::packAndSendToFriendsOf(UserPacket* packet, int id) const
{
	for (int i = 1; i < getPlayers().size(); i++)
	{
		if (id == i) // Client verwaltet sich selbst
			continue;

		if (getPlayer(id)->getTeamUserPacket()->getTeam()->isFriendlyTeam(getPlayer(i)->getTeamUserPacket()->getTeam()))
		{
			UserPacketWithID* upwid = new UserPacketWithID(packet, id);
			send(upwid, getPlayer(i)->getIP());
			deleteAndNULL(upwid);
		}
	}
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
	getUpdatedPlayer(id)->applyLockUserPacket(packet);
	packAndSendToAllClients(packet, id);
}

void ServerLobbyMenu::handleDisconnectUserPacket(DisconnectUserPacket* packet, int id)
{
	removePlayer(id);
	packAndSendToAllClients(packet, id);

	unlockAll();
	updatePlayerIcons();
}

void ServerLobbyMenu::handleTeamUserPacket(TeamUserPacket* packet, int id)
{
	getPlayer(id)->applyTeamUserPacket(packet);
	getUpdatedPlayer(id)->applyTeamUserPacket(packet);
	packAndSendToAllClients(packet, id);

	unlockAll();
	updatePlayerIcons();
}

void ServerLobbyMenu::handleLoginUserPacket(LoginUserPacket* packet, sf::IpAddress* ip)
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
			deleteAndNULL(mapPacket);
		}
		addPlayer(player);
		addUpdatedPlayer(player);
		deleteAndNULL(player);
		packAndSendToAllClients(packet, ipToID(ip, getPlayers())); // das erhaltene packet wird an alle clients weitergegeben

		unlockAll();
		updatePlayerIcons();
	}
	else
	{
		Debug::warn("ServerLobbyMenu.handleLoginUserPacket(): Spieler wollte ein zweites mal joinen");
	}
}

void ServerLobbyMenu::handleAvatarUserPacket(AvatarUserPacket* packet, int id)
{
	Debug::warnIf(getPlayer(id) == NULL, "ServerLobbyMenu::handleAvatarUserPacket(): no Player with id " + Converter::intToString(id));

	// Wenn Spieler sich im gleichen Team befindet, wie Server (ich)
	if (getPlayer(id)->getTeamUserPacket()->getTeam()->isFriendlyTeam(getLocalPlayer()->getTeamUserPacket()->getTeam()))
	{
		getPlayer(id)->applyAvatarUserPacket(packet);
	}

	packAndSendToFriendsOf(packet, id);
	getUpdatedPlayer(id)->applyAvatarUserPacket(packet);
}

void ServerLobbyMenu::handleSkillUserPacket(SkillUserPacket* packet, int id)
{
	Debug::warnIf(getPlayer(id) == NULL, "ServerLobbyMenu::handleSkillUserPacket(): no Player with id " + Converter::intToString(id));

	// Wenn Spieler sich im gleichen Team befindet, wie Server (ich)
	if (getPlayer(id)->getTeamUserPacket()->getTeam()->isFriendlyTeam(getLocalPlayer()->getTeamUserPacket()->getTeam()))
	{
		getPlayer(id)->applySkillUserPacket(packet);
	}

	packAndSendToFriendsOf(packet, id);
	getUpdatedPlayer(id)->applySkillUserPacket(packet);
}

void ServerLobbyMenu::handleItemUserPacket(ItemUserPacket* packet, int id)
{
	Debug::warnIf(getPlayer(id) == NULL, "ServerLobbyMenu::handleItemUserPacket(): no Player with id " + Converter::intToString(id));

	// Wenn Spieler sich im gleichen Team befindet, wie Server (ich)
	if (getPlayer(id)->getTeamUserPacket()->getTeam()->isFriendlyTeam(getLocalPlayer()->getTeamUserPacket()->getTeam()))
	{
		getPlayer(id)->applyItemUserPacket(packet);
	}

	packAndSendToFriendsOf(packet, id);
	getUpdatedPlayer(id)->applyItemUserPacket(packet);
}

void ServerLobbyMenu::playerPropertySelected(PlayerPropertyUserPacket* packet)
{
	switch (packet->getCID())
	{
		case AVATAR_USER_PACKET_CID:
			getLocalPlayer()->applyAvatarUserPacket(dynamic_cast<AvatarUserPacket*>(packet));
			getUpdatedLocalPlayer()->applyAvatarUserPacket(dynamic_cast<AvatarUserPacket*>(packet));
			break;
		case SKILL_USER_PACKET_CID:
			getLocalPlayer()->applySkillUserPacket(dynamic_cast<SkillUserPacket*>(packet));
			getUpdatedLocalPlayer()->applySkillUserPacket(dynamic_cast<SkillUserPacket*>(packet));
			break;
		case ITEM_USER_PACKET_CID:
			getLocalPlayer()->applyItemUserPacket(dynamic_cast<ItemUserPacket*>(packet));
			getUpdatedLocalPlayer()->applyItemUserPacket(dynamic_cast<ItemUserPacket*>(packet));
			break;
		default:
			Debug::warn("ServerLobbyMenu::playerPropertySelected(): awkward packet");
	}
	packAndSendToFriendsOf(packet, 0);
}

LobbyPlayer* ServerLobbyMenu::getUpdatedPlayer(int id) const
{
	Debug::warnIf(id < 0 || id >= getUpdatedPlayers().size(), "ServerLobbyMenu::getUpdatedPlayers(): size == 0");
	return getUpdatedPlayers()[id];
}

LobbyPlayer* ServerLobbyMenu::getUpdatedLocalPlayer() const
{
	return getUpdatedPlayers()[0];
}

std::vector<LobbyPlayer*> ServerLobbyMenu::getUpdatedPlayers() const
{
	return updatedPlayers;
}

void ServerLobbyMenu::addUpdatedPlayer(LobbyPlayer* p)
{
	updatedPlayers.push_back(new LobbyPlayer(p));
}

void ServerLobbyMenu::addPlayer(LobbyPlayer* p)
{
	LobbyMenu::addPlayer(new LobbyPlayer(p));
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
		case PREGAME_PHASE:
			lockButton->setEnabled(areAllClientsLocked());
		break;
	}
}

void ServerLobbyMenu::updatePlayers()
{
	clearPlayers(); // doesn't clear the updatedPlayers
	for (int i = 0; i < getUpdatedPlayers().size(); i++)
	{
		addPlayer(getUpdatedPlayers()[i]);
	}
	LobbyPlayersPacket* p = new LobbyPlayersPacket(getUpdatedPlayers());
	sendToAllClients(p);
	deleteAndNULL(p);
}

void ServerLobbyMenu::nextPhase()
{
	if (getPhase() == TEAM_PHASE)
	{
		mapSelectButton->setEnabled(false);
		mapSelectEditField->setEnabled(false);
	}
	LobbyMenu::nextPhase();
	if (getPhase() == AVATAR_PHASE+1 || getPhase() == SKILL_PHASE+1 || getPhase() == ITEM_PHASE+1)
	{
		updatePlayers();
	}
	updatePlayerIcons();
}

void ServerLobbyMenu::unlockAll()
{
	LobbyMenu::unlockAll();
	LockUserPacket* packet = new LockUserPacket(false);
	for (int i = 0; i < getUpdatedPlayers().size(); i++)
	{
		getUpdatedPlayers()[i]->applyLockUserPacket(packet);
	}
	delete packet;
}

void ServerLobbyMenu::removePlayer(int id)
{
	LobbyMenu::removePlayer(id);
	deleteAndNULL(updatedPlayers[id]);
	updatedPlayers.erase(updatedPlayers.begin() + id);
}

void ServerLobbyMenu::createGameInterface()
{
	Main::getMenuList()->addMenu(new ServerGameInterface(getLobbyTileMap(), getPlayers()));
}
