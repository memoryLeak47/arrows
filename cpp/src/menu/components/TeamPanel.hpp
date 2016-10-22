#ifndef __TEAMPANEL_CLASS__
#define __TEAMPANEL_CLASS__

class LobbyMenu;
class TeamListPanel;
class PixelRect;
class Team;
class LobbyPlayer;
class Button;

#include "Panel.hpp"
#include <vector>

class TeamPanel : public Panel
{
	public:
		TeamPanel(LobbyMenu*, TeamListPanel*, const PixelRect&, Team*);
		void update(const std::vector<LobbyPlayer*>&);
		LobbyMenu* getLobbyMenu() const;
		Team* getTeam() const;
		void disableTeamButton();
	private:
		LobbyMenu* lobby;
		Button* teamButton;
		Team* team;
};

#endif
