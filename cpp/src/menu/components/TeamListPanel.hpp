#ifndef __TEAMLISTPANEL_CLASS__
#define __TEAMLISTPANEL_CLASS__

#include "Panel.hpp"

class LobbyMenu;

class TeamListPanel : public Panel
{
	public:
		TeamListPanel(LobbyMenu*, const PixelRect&);
		void update();
		LobbyMenu* getLobbyMenu() const;
		void disableTeamButtons();
	private:
		LobbyMenu* lobby;
};

#include "../menues/LobbyMenu.hpp"

#endif
