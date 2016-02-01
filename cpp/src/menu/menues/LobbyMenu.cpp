#include "LobbyMenu.hpp"

#include "../components/Label.hpp"
#include "../../core/Main.hpp"
#include "../../misc/Debug.hpp"

LobbyMenu::LobbyMenu()
{
	phase = TEAM_PHASE;
	
	addComponent(new Label(this, PixelRect(300, 10, 150, 20), "Lobby"));
	addComponent(teamListPanel = new TeamListPanel(this, PixelRect(100, 100, 600, 600)));

	class LockButton : public Button
	{
		public:
			LockButton(LobbyMenu* c, const PixelRect& r, const std::string& s) : Button(c, r, s) {}
			void onClick(int mouseButton)
			{
				((LobbyMenu*)getParent())->lockPressed();
			}
	};
	addComponent(lockButton = new LockButton(this, PixelRect(SCREEN_SIZE_X - 250, 600, 200, 60), "Lock"));

	addComponent(miniMap = new LobbyMiniMap(this, PixelRect(SCREEN_SIZE_X - 250, 100, 200, 140)));

	class DisconnectButton : public Button
	{
		public:
			DisconnectButton(LobbyMenu* c, const PixelRect& r, const std::string& s) : Button(c, r, s) {}
			void onClick(int mouseButton)
			{
				((LobbyMenu*)getParent())->disconnectPressed();
			}
	};
	addComponent(new DisconnectButton(this, PixelRect(20, 500, 20, 20), "Disconnect"));

}

int LobbyMenu::getPhase() const
{
	return phase;
}

std::vector<LobbyPlayer*> LobbyMenu::getPlayers() const
{
	return players;
}

void LobbyMenu::handlePacket(Packet* packet, const sf::IpAddress& ip)
{
	Debug::warnIf(packet == NULL, "LobbyMenu::handlePacket(): packet == NULL");
	if (typeid(packet) == typeid(LockUserPacket))
	{
		handleLockUserPacket((LockUserPacket*) packet, ipToID(ip, getPlayers()));
	}
}

void LobbyMenu::handlePacketByID(Packet* packet, int id)
{
	if (typeid(packet) == typeid(LockUserPacket))
	{
		handleLockUserPacket((LockUserPacket*) packet, id);
	}
	else if (typeid(packet) == typeid(DisconnectUserPacket))
	{
		handleDisconnectUserPacket((DisconnectUserPacket*) packet, id);
	}
	else if (typeid(packet) == typeid(TeamUserPacket))
	{
		handleTeamUserPacket((TeamUserPacket*) packet, id);
	}
	else if (typeid(packet) == typeid(LoginUserPacket))
	{
		handleLoginUserPacket((LoginUserPacket*) packet, id);
	}
	else if (typeid(packet) == typeid(AvatarUserPacket))
	{
		handleAvatarUserPacket((AvatarUserPacket*) packet, id);
	}
	else if (typeid(packet) == typeid(SkillUserPacket))
	{
		handleSkillUserPacket((SkillUserPacket*) packet, id);
	}
	else if (typeid(packet) == typeid(ItemUserPacket))
	{
		handleItemUserPacket((ItemUserPacket*) packet, id);
	}
	else if (typeid(packet) == typeid(MapPacket))
	{
		handleMapPacket((MapPacket*) packet, id);
	}
	else if (typeid(packet) == typeid(UserPacketWithID))
	{
		handlePacketByID(((UserPacketWithID*)packet)->getPacket(), ((UserPacketWithID*) packet)->getID());
	}
	else if (typeid(packet) == typeid(LobbyPlayersPacket))
	{
		handleLobbyPlayersPacket((LobbyPlayersPacket*) packet, id);
	}
	else
	{
		Debug::warn("LobbyMenu::handlePacketByID(): unhandled packet");
	}
}

int LobbyMenu::ipToID(const sf::IpAddress& ip, const std::vector<LobbyPlayer*>& players) const
{
	for (int i = 0; i < players.size(); i++)
	{
		if (players[i]->getIP() == ip)
		{
			return i;
		}
	}
	Debug::warn("LobbyMenu::ipToID(): no Player with this ip: " + ip.toString());
	return -1;
}

void LobbyMenu::updatePlayerIcons() const
{
	// TODO
}

void LobbyMenu::handleLockUserPacket(LockUserPacket*, int)
{
	Debug::warn("LobbyMenu::handleLockUserPacket(): should not be called, maybe forgotten to overwrite");
}

void LobbyMenu::handleDisconnectUserPacket(DisconnectUserPacket*, int)
{
	Debug::warn("LobbyMenu::handleDisconnectUserPacket(): should not be called, maybe forgotten to overwrite");
}

void LobbyMenu::handleTeamUserPacket(TeamUserPacket*, int)
{
	Debug::warn("LobbyMenu::handleTeamUserPacket(): should not be called, maybe forgotten to overwrite");
}

void LobbyMenu::handleLoginUserPacket(LoginUserPacket*, int)
{
	Debug::warn("LobbyMenu::handleLoginUserPacket(): should not be called, maybe forgotten to overwrite");
}

void LobbyMenu::handleAvatarUserPacket(AvatarUserPacket*, int)
{
	Debug::warn("LobbyMenu::handleAvatarUserPacket(): should not be called, maybe forgotten to overwrite");
}

void LobbyMenu::handleSkillUserPacket(SkillUserPacket*, int)
{
	Debug::warn("LobbyMenu::handleSkillUserPacket(): should not be called, maybe forgotten to overwrite");
}

void LobbyMenu::handleItemUserPacket(ItemUserPacket*, int)
{
	Debug::warn("LobbyMenu::handleItemUserPacket(): should not be called, maybe forgotten to overwrite");
}

void LobbyMenu::handleMapPacket(MapPacket*, int)
{
	Debug::warn("LobbyMenu::handleMapPacket(): should not be called, maybe forgotten to overwrite");
}

void LobbyMenu::handleUserPacketWithID(UserPacketWithID*, int)
{
	Debug::warn("LobbyMenu::handleUserPacketWithID(): should not be called, maybe forgotten to overwrite");
}

void LobbyMenu::handleLobbyPlayersPacket(LobbyPlayersPacket*, int)
{
	Debug::warn("LobbyMenu::handleLobbyPlayersPacket(): should not be called, maybe forgotten to overwrite");
}
