#include "ServerLobbyMenu.hpp"

#include <misc/Global.hpp>
#include <menu/MenuList.hpp>
#include <core/Main.hpp>
#include <core/Screen.hpp>
#include <misc/Account.hpp>
#include <game/ServerGameInterface.hpp>
#include <network/packets/LockPacket.hpp>
#include <network/packets/LoginPacket.hpp>
#include <network/packets/AvatarPacket.hpp>
#include <network/packets/SkillPacket.hpp>
#include <network/packets/ItemPacket.hpp>
#include <network/packets/TeamPacket.hpp>
#include <network/packets/LobbyPlayersPacket.hpp>
#include <network/packets/DisconnectPacket.hpp>
#include <network/packets/MapPacket.hpp>
#include <network/packets/PacketWithID.hpp>
#include <player/LobbyPlayer.hpp>
#include <menu/components/EditField.hpp>
#include <menu/components/Button.hpp>
#include <tilemap/LobbyTileMap.hpp>
#include <team/Team.hpp>

ServerLobbyMenu::ServerLobbyMenu()
	: LobbyMenu("next Phase")
{
	addComponent(mapSelectEditField = new EditField(this, PixelRect(Screen::getSize().x-240, 250, 50, 20), "default"));

	// Map Select - Button
	class MapSelectButton : public Button
	{
		public:
			MapSelectButton(ServerLobbyMenu* c, const PixelRect& r, const std::string& s) : Button(c, r, s), menu(c) {}
			virtual void onPress() override
			{
				menu->mapSelected();
			}
		private:
			ServerLobbyMenu* menu;
	};
	addComponent(mapSelectButton = new MapSelectButton(this, PixelRect(Screen::getSize().x-180, 250, 50, 20), "Ok"));

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
	deleteAndNullptr(mapPacket);

	unlockAll();
}

void ServerLobbyMenu::handlePacket(Packet* packet, sf::IpAddress* ip)
{
	if (packet->getCompressID() == LOCK_PACKET_CID)
	{
		handleLockPacket(packet->unwrap<LockPacket>(), ipToID(ip, getPlayers()));
	}
	else if (packet->getCompressID() == DISCONNECT_PACKET_CID)
	{
		handleDisconnectPacket(packet->unwrap<DisconnectPacket>(), ipToID(ip, getPlayers()));
	}
	else if (packet->getCompressID() == TEAM_PACKET_CID && getPhase() == TEAM_PHASE)
	{
		handleTeamPacket(packet->unwrap<TeamPacket>(), ipToID(ip, getPlayers()));
	}
	else if (packet->getCompressID() == LOGIN_PACKET_CID && getPhase() == TEAM_PHASE)
	{
		handleLoginPacket(packet->unwrap<LoginPacket>(), ip);
	}
	else if (packet->getCompressID() == AVATAR_PACKET_CID && getPhase() == AVATAR_PHASE)
	{
		handleAvatarPacket(packet->unwrap<AvatarPacket>(), ipToID(ip, getPlayers()));
	}
	else if (packet->getCompressID() == SKILL_PACKET_CID && getPhase() == SKILL_PHASE)
	{
		handleSkillPacket(packet->unwrap<SkillPacket>(), ipToID(ip, getPlayers()));
	}
	else if (packet->getCompressID() == ITEM_PACKET_CID && getPhase() == ITEM_PHASE)
	{
		handleItemPacket(packet->unwrap<ItemPacket>(), ipToID(ip, getPlayers()));
	}
	else
	{
		Debug::warn("ServerLobbyMenu::handlePacket(): awkward packet(" + Converter::intToString((int) packet->getCompressID()) + ") in awkward phase(" + Converter::intToString(getPhase()) + ")");
	}
	deleteAndNullptr(packet);
}

void ServerLobbyMenu::createServerPlayer()
{
	LoginPacket* packet = new LoginPacket(Main::getAccount()->getName(), Main::getAccount()->getRank());
	LobbyPlayer* me = new LobbyPlayer(packet);
	addPlayer(me);
	addUpdatedPlayer(me);
	deleteAndNullptr(me);
	deleteAndNullptr(packet);
}

void ServerLobbyMenu::lockPressed()
{
	LockPacket* l = new LockPacket(!getLocalPlayer()->getLockPacket()->isLocked());
	packAndSendToAllClients(l, 0);
	deleteAndNullptr(l);
	nextPhase();
}

void ServerLobbyMenu::disconnectPressed()
{
	DisconnectPacket* dis = new DisconnectPacket();
	packAndSendToAllClients(dis, 0);
	deleteAndNullptr(dis);
	Main::getMenuList()->back();
}

void ServerLobbyMenu::teamPressed(Team* team)
{
	TeamPacket* packet = new TeamPacket(team->getID());
	getLocalPlayer()->applyTeamPacket(packet);
	getUpdatedLocalPlayer()->applyTeamPacket(packet);
	packAndSendToAllClients(packet, 0);
	deleteAndNullptr(packet);

	unlockAll();
	updatePlayerIcons();
}

LobbyPlayer* ServerLobbyMenu::getLocalPlayer() const
{
	if (getPlayers().size() == 0) Debug::warn("ServerLobbyMenu::getLocalPlayer(): getPlayers().size() == 0 -> is probably nullptr");
	return getPlayer(0);
}

void ServerLobbyMenu::packAndSendToAllClients(Packet* p, int id) const
{
	PacketWithID* packet = new PacketWithID(p, id);
	for (unsigned int i = 1; i < getPlayers().size(); i++)
	{
		send(packet, getPlayer(i)->getIP());
	}
	deleteAndNullptr(packet);
}

void ServerLobbyMenu::packAndSendToFriendsOf(Packet* packet, int id) const
{
	for (unsigned int i = 1; i < getPlayers().size(); i++)
	{
		if (id == (int)i) // Client verwaltet sich selbst
			continue;

		if (getPlayer(id)->getTeamPacket()->getTeam()->isFriendlyTeam(getPlayer(i)->getTeamPacket()->getTeam()))
		{
			PacketWithID* upwid = new PacketWithID(packet, id);
			send(upwid, getPlayer(i)->getIP());
			deleteAndNullptr(upwid);
		}
	}
}

void ServerLobbyMenu::sendToAllClients(Packet* packet) const
{
	for (unsigned int i = 1; i < getPlayers().size(); i++)
	{
		send(packet, getPlayer(i)->getIP());
	}
}

void ServerLobbyMenu::handleLockPacket(LockPacket* packet, int id)
{
	getPlayer(id)->applyLockPacket(packet);
	getUpdatedPlayer(id)->applyLockPacket(packet);
	packAndSendToAllClients(packet, id);
}

void ServerLobbyMenu::handleDisconnectPacket(DisconnectPacket* packet, int id)
{
	removePlayer(id);
	packAndSendToAllClients(packet, id);

	unlockAll();
	updatePlayerIcons();
}

void ServerLobbyMenu::handleTeamPacket(TeamPacket* packet, int id)
{
	getPlayer(id)->applyTeamPacket(packet);
	getUpdatedPlayer(id)->applyTeamPacket(packet);
	packAndSendToAllClients(packet, id);

	unlockAll();
	updatePlayerIcons();
}

void ServerLobbyMenu::handleLoginPacket(LoginPacket* packet, sf::IpAddress* ip)
{
	if (ipToID(ip, getPlayers()) == -1) // Wenn es noch keinen Spieler mit dieser IP gibt
	{
		LobbyPlayer* player = new LobbyPlayer(packet, ip);
		if (TAG_STATUS) Debug::note("ServerLobbyMenu.handleLoginPacket(): Player \"" + player->getLoginPacket()->getName() + "\" joined the Game and is happy :)");
		LobbyPlayersPacket* playersPacket = new LobbyPlayersPacket(getPlayers()); // 
		send(playersPacket, ip); // liste ohne den Neuen an den Neuen senden.
		if (getLobbyTileMap()->isValid())
		{
			MapPacket* mapPacket = new MapPacket(getLobbyTileMap()->getInts());
			send(mapPacket, ip); // Die Map des neuen wird gesetzt
			deleteAndNullptr(mapPacket);
		}
		addPlayer(player);
		addUpdatedPlayer(player);
		deleteAndNullptr(player);
		packAndSendToAllClients(packet, ipToID(ip, getPlayers())); // das erhaltene packet wird an alle clients weitergegeben

		unlockAll();
		updatePlayerIcons();
	}
	else
	{
		Debug::warn("ServerLobbyMenu.handleLoginPacket(): Spieler wollte ein zweites mal joinen");
	}
}

void ServerLobbyMenu::handleAvatarPacket(AvatarPacket* packet, int id)
{
	if (getPlayer(id) == nullptr) Debug::warn("ServerLobbyMenu::handleAvatarPacket(): no Player with id " + Converter::intToString(id));

	// Wenn Spieler sich im gleichen Team befindet, wie Server (ich)
	if (getPlayer(id)->getTeamPacket()->getTeam()->isFriendlyTeam(getLocalPlayer()->getTeamPacket()->getTeam()))
	{
		getPlayer(id)->applyAvatarPacket(packet);
	}

	packAndSendToFriendsOf(packet, id);
	getUpdatedPlayer(id)->applyAvatarPacket(packet);
}

void ServerLobbyMenu::handleSkillPacket(SkillPacket* packet, int id)
{
	if (getPlayer(id) == nullptr) Debug::warn("ServerLobbyMenu::handleSkillPacket(): no Player with id " + Converter::intToString(id));

	// Wenn Spieler sich im gleichen Team befindet, wie Server (ich)
	if (getPlayer(id)->getTeamPacket()->getTeam()->isFriendlyTeam(getLocalPlayer()->getTeamPacket()->getTeam()))
	{
		getPlayer(id)->applySkillPacket(packet);
	}

	packAndSendToFriendsOf(packet, id);
	getUpdatedPlayer(id)->applySkillPacket(packet);
}

void ServerLobbyMenu::handleItemPacket(ItemPacket* packet, int id)
{
	if (getPlayer(id) == nullptr) Debug::warn("ServerLobbyMenu::handleItemPacket(): no Player with id " + Converter::intToString(id));

	// Wenn Spieler sich im gleichen Team befindet, wie Server (ich)
	if (getPlayer(id)->getTeamPacket()->getTeam()->isFriendlyTeam(getLocalPlayer()->getTeamPacket()->getTeam()))
	{
		getPlayer(id)->applyItemPacket(packet);
	}

	packAndSendToFriendsOf(packet, id);
	getUpdatedPlayer(id)->applyItemPacket(packet);
}

void ServerLobbyMenu::playerPropertySelected(PlayerPropertyPacket* packet)
{
	switch (packet->getCompressID())
	{
		case AVATAR_PACKET_CID:
			getLocalPlayer()->applyAvatarPacket(packet->unwrap<AvatarPacket>());
			getUpdatedLocalPlayer()->applyAvatarPacket(packet->unwrap<AvatarPacket>());
			break;
		case SKILL_PACKET_CID:
			getLocalPlayer()->applySkillPacket(packet->unwrap<SkillPacket>());
			getUpdatedLocalPlayer()->applySkillPacket(packet->unwrap<SkillPacket>());
			break;
		case ITEM_PACKET_CID:
			getLocalPlayer()->applyItemPacket(packet->unwrap<ItemPacket>());
			getUpdatedLocalPlayer()->applyItemPacket(packet->unwrap<ItemPacket>());
			break;
		default:
			Debug::warn("ServerLobbyMenu::playerPropertySelected(): awkward packet");
	}
	packAndSendToFriendsOf(packet, 0);
}

LobbyPlayer* ServerLobbyMenu::getUpdatedPlayer(int id) const
{
	if (id < 0 || id >= (int)getUpdatedPlayers().size()) Debug::warn("ServerLobbyMenu::getUpdatedPlayers(): size == 0");
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
			lockButton->setEnabled(areAllClientsLocked() && getLocalPlayer()->getAvatarPacket()->isValid());
		break;
		case SKILL_PHASE:
			lockButton->setEnabled(areAllClientsLocked() && getLocalPlayer()->getSkillPacket()->isValid());
		break;
		case ITEM_PHASE:
			lockButton->setEnabled(areAllClientsLocked() && getLocalPlayer()->getItemPacket()->isValid());
		break;
		case PREGAME_PHASE:
			lockButton->setEnabled(areAllClientsLocked());
		break;
	}
}

void ServerLobbyMenu::updatePlayers()
{
	clearPlayers(); // doesn't clear the updatedPlayers
	for (unsigned int i = 0; i < getUpdatedPlayers().size(); i++)
	{
		addPlayer(getUpdatedPlayers()[i]);
	}
	LobbyPlayersPacket* p = new LobbyPlayersPacket(getUpdatedPlayers());
	sendToAllClients(p);
	deleteAndNullptr(p);
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
	LockPacket* packet = new LockPacket(false);
	for (unsigned int i = 0; i < getUpdatedPlayers().size(); i++)
	{
		getUpdatedPlayers()[i]->applyLockPacket(packet);
	}
	delete packet;
}

void ServerLobbyMenu::removePlayer(int id)
{
	LobbyMenu::removePlayer(id);
	deleteAndNullptr(updatedPlayers[id]);
	updatedPlayers.erase(updatedPlayers.begin() + id);
}

void ServerLobbyMenu::createGameInterface()
{
	Main::getMenuList()->addMenu(new ServerGameInterface(getLobbyTileMap(), getPlayers()));
}
