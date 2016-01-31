#ifndef __LOBBYMENU_CLASS__
#define __LOBBYMENU_CLASS__

#define TEAM_PHASE 0
#define AVATAR_PHASE 1
#define SKILL_PHASE 2
#define ITEM_PHASE 3
#define GAME_PHASE 4

#include <SFML/Network.hpp>
#include <vector>

#include "../NetworkingMenu.h"

class Button;
class LobbyTileMap;
class LobbyMiniMap;
class LobbyPlayer;
class TeamListPanel;
class LockUserPacket;
class DisconnectUserPacket;
class TeamUserPacket;
class LoginUserPacket;
class AvatarUserPacket;
class SkillUserPacket;
class ItemUserPacket;
class MapPacket;
class UserPacketWithID;
class LobbyPlayersPacket;

class LobbyMenu : public NetworkingMenu
{
	public:
		LobbyMenu();
		int getPhase() const;
		std::vector<LobbyPlayer*> getPlayers() const;
		virtual void handlePacket(Packet*, const sf::IpAddress&) override;
	protected:
		int ipToID(const sf::IpAddress&, const std::vector<LobbyPlayer*>&) const;
		void handlePacketByID(Packet*, int);
		virtual void lockPressed() = 0;
		virtual void disconnectPressed() = 0;
		// handle Packets
		virtual void handleLockUserPacket(LockUserPacket*, int);
		virtual void handleDisconnectUserPacket(DisconnectUserPacket*, int);
		virtual void handleTeamUserPacket(TeamUserPacket*, int);
		virtual void handleLoginUserPacket(LoginUserPacket*, int);
		virtual void handleAvatarUserPacket(AvatarUserPacket*, int);
		virtual void handleSkillUserPacket(SkillUserPacket*, int);
		virtual void handleItemUserPacket(ItemUserPacket*, int);
		virtual void handleMapPacket(MapPacket*, int);
		virtual void handleUserPacketWithID(UserPacketWithID*, int);
		virtual void handleLobbyPlayersPacket(LobbyPlayersPacket*, int);

		Button* lockButton; // Verweiß auf den NextStep/LockIn Button
	private:
		int phase;
		LobbyTileMap* lobbyTileMap;
		LobbyMiniMap* miniMap;
		std::vector<LobbyPlayer*> players; // Bluemi: protected -> private; added setter
		TeamListPanel* teamListPanel; // Nicht zwingend nötig, nur einfacherer Zugriff, da nicht über index
};

#include "../components/Button.h"
#include "../../tile/map/LobbyTileMap.h"
#include "../components/LobbyMiniMap.h"
#include "../../player/LobbyPlayer.h"
#include "../components/TeamListPanel.h"
#include "../../network/packets/LockUserPacket.h"
#include "../../network/packets/DisconnectUserPacket.h"
#include "../../network/packets/TeamUserPacket.h"
#include "../../network/packets/LoginUserPacket.h"
#include "../../network/packets/AvatarUserPacket.h"
#include "../../network/packets/SkillUserPacket.h"
#include "../../network/packets/ItemUserPacket.h"
#include "../../network/packets/MapPacket.h"
#include "../../network/packets/UserPacketWithID.h"
#include "../../network/packets/LobbyPlayersPacket.h"

#endif
