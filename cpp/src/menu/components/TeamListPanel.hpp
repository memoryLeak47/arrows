#ifndef __TEAMLISTPANEL_CLASS__
#define __TEAMLISTPANEL_CLASS__

class LobbyMenu;
class PixelRect;

#include "Panel.hpp"

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

#endif
