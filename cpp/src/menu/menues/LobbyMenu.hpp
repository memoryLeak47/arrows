#ifndef __LOBBYMENU_CLASS__
#define __LOBBYMENU_CLASS__

enum LobbyPhase { TEAM_PHASE, AVATAR_PHASE, SKILL_PHASE, ITEM_PHASE, PREGAME_PHASE, GAME_PHASE };

class LobbyPlayer;
class Team;
class PlayerPropertyPacket;
class LobbyTileMap;
class Button;
class LobbyTileMap;
class LobbyMiniMap;
class TeamListPanel;

#include <menu/Menu.hpp>
#include <network/NetworkInterface.hpp>
#include <vector>
#include <SFML/Network/IpAddress.hpp>

class LobbyMenu : public Menu, public NetworkInterface
{
	public:
		LobbyMenu(std::string lockButtonText);
		virtual ~LobbyMenu();
		std::vector<LobbyPlayer*> getPlayers() const;
		int getPhase() const;
		virtual void tick() override;
		virtual void lockPressed() = 0;
		virtual void disconnectPressed() = 0;
		virtual void teamPressed(Team*) = 0;
		virtual LobbyPlayer* getLocalPlayer() const = 0;
		virtual void playerPropertySelected(PlayerPropertyPacket*) = 0;
		LobbyTileMap* getLobbyTileMap() const;
	protected:
		bool areAllClientsLocked() const;
		int ipToID(sf::IpAddress*, const std::vector<LobbyPlayer*>&) const;
		void updatePlayerIcons() const;
		LobbyPlayer* getPlayer(int) const;
		virtual void addPlayer(LobbyPlayer*);
		virtual void updateLockButton() const = 0;
		void updateMap(const std::vector<std::vector<int>>&);
        	virtual void unlockAll();
		virtual void nextPhase();
		virtual void removePlayer(int);
		void clearPlayers();
		void resetLobby();

		Button* lockButton; // Verweiß auf den NextStep/LockIn Button
	private:
		int phase;
		LobbyTileMap* tileMap;
		LobbyMiniMap* miniMap;
		std::vector<LobbyPlayer*> players; // Bluemi: protected -> private; added setter
		TeamListPanel* teamListPanel; // Nicht zwingend nötig, nur einfacherer Zugriff, da nicht über index
};

#endif
