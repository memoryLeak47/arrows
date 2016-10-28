#ifndef __TEAMLISTPANEL_CLASS__
#define __TEAMLISTPANEL_CLASS__

class LobbyMenu;
class PixelRect;
class TeamPanel;

#include "Panel.hpp"
#include <vector>

class TeamListPanel : public Panel
{
	public:
		TeamListPanel(LobbyMenu*, const PixelRect&);
		void update();
		LobbyMenu* getLobbyMenu() const;
		void disableTeamButtons();
	private:
		std::vector<TeamPanel*> teamPanels;
		LobbyMenu* lobby;
};

#endif
