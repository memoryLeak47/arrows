#ifndef __LOBBYMENU_CLASS__
#define __LOBBYMENU_CLASS__

#define TEAM_PHASE 0
#define AVATAR_PHASE 1
#define SKILL_PHASE 2
#define ITEM_PHASE 3
#define GAME_PHASE 4

#include <vector>
#include <SFML/Network.hpp>

#include "../NetworkingMenu.hpp"

#include "../../tile/map/LobbyTileMap.hpp"

class Button;
class Team;
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
class PlayerPropertyUserPacket;

class LobbyMenu : public NetworkingMenu
{
	public:
		LobbyMenu();
		virtual ~LobbyMenu();
		std::vector<LobbyPlayer*> getPlayers() const;
		int getPhase() const;
		virtual void tick() override;
		virtual void lockPressed() = 0;
		virtual void disconnectPressed() = 0;
		virtual void teamPressed(Team*) = 0;
		virtual LobbyPlayer* getLocalPlayer() const = 0;
		virtual void playerPropertySelected(PlayerPropertyUserPacket*) = 0;
		LobbyTileMap* getLobbyTileMap() const;
	protected:
		bool areAllClientsLocked() const;
		int ipToID(const sf::IpAddress&, const std::vector<LobbyPlayer*>&) const;
		void updatePlayerIcons() const;
		LobbyPlayer* getPlayer(int) const;
		virtual void addPlayer(LobbyPlayer*);
		virtual void updateLockButton() const = 0;
		void updateMap(const std::vector<std::vector<int>>&);
        	virtual void unlockAll();
		virtual void nextPhase();
		virtual void removePlayer(int);
		void clearPlayers();
		Button* lockButton; // Verweiß auf den NextStep/LockIn Button
	private:
		int phase;
		LobbyTileMap* tileMap;
		LobbyMiniMap* miniMap;
		std::vector<LobbyPlayer*> players; // Bluemi: protected -> private; added setter
		TeamListPanel* teamListPanel; // Nicht zwingend nötig, nur einfacherer Zugriff, da nicht über index
};

#include "../components/Button.hpp"
#include "../../player/property/Team.hpp"
#include "../components/LobbyMiniMap.hpp"
#include "../../player/LobbyPlayer.hpp"
#include "../components/TeamListPanel.hpp"
#include "../../network/packets/LockUserPacket.hpp"
#include "../../network/packets/DisconnectUserPacket.hpp"
#include "../../network/packets/TeamUserPacket.hpp"
#include "../../network/packets/LoginUserPacket.hpp"
#include "../../network/packets/AvatarUserPacket.hpp"
#include "../../network/packets/SkillUserPacket.hpp"
#include "../../network/packets/ItemUserPacket.hpp"
#include "../../network/packets/MapPacket.hpp"
#include "../../network/packets/UserPacketWithID.hpp"
#include "../../network/packets/LobbyPlayersPacket.hpp"
#include "../../network/packets/PlayerPropertyUserPacket.hpp"

#endif
