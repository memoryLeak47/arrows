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
	private:
		void createTeamPanels();
};

#include "../menues/LobbyMenu.hpp"

#endif
