#ifndef __LOBBYMENU_CLASS__
#define __LOBBYMENU_CLASS__

#define TEAM_PHASE 0
#define AVATAR_PHASE 1
#define SKILL_PHASE 2
#define ITEM_PHASE 3
#define GAME_PHASE 4

#include <vector>

#include "../NetworkingMenu.h"

class Button;
class LobbyTileMap;
class LobbyMiniMap;
class LobbyPlayer;
class TeamListPanel;

class LobbyMenu : public NetworkingMenu
{
	public:
		LobbyMenu();
	protected:
		virtual void lockPressed() = 0;
		virtual void disconnectPressed() = 0;

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

#endif
