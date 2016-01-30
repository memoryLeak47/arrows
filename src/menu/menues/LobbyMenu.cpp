#include "LobbyMenu.h"

#include "../components/Label.h"

LobbyMenu::LobbyMenu()
{
	phase = TEAM_PHASE;
	
	addComponent(new Label(this, PixelRect(300, 10, 150, 20), "Lobby"));
	addComponent(teamListPanel = new TeamListPanel(this, PixelRect(100, 100, 600, 600)));

}
