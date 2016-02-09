#ifndef __TEAMPANEL_CLASS__
#define __TEAMPANEL_CLASS__

#include <vector>

#include "Panel.hpp"

class Team;
class Button;
class TeamListPanel;
class LobbyPlayer;
class LobbyMenu;

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

#include "../../player/property/Team.hpp"
#include "Button.hpp"
#include "TeamListPanel.hpp"
#include "../../player/LobbyPlayer.hpp"
#include "../menues/LobbyMenu.hpp"

#endif
