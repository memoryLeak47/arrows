#include "TeamListPanel.hpp"

#include <misc/Global.hpp>
#include "TeamPanel.hpp"
#include <team/Team.hpp>
#include <menu/menues/LobbyMenu.hpp>

TeamListPanel::TeamListPanel(LobbyMenu* c, const PixelRect& r) : Panel(c, r), lobby(c)
{
	update();
}

void TeamListPanel::update()
{
	// Formatieren der TeamPanels (nach unten rutschen, falls das obere Panel zu weit nach unten reicht)
	clearComponents();
	for (unsigned int i = 0; i < Team::getAmount(); i++) // für alle TeamPanels updaten + formatieren
	{
		if (i == 0)
		{
			TeamPanel* panel = new TeamPanel(getLobbyMenu(), this, PixelRect(20, 20+100*i, 140, 60), Team::get(i));
			addComponent(panel);
			teamPanels.push_back(panel);
		}
		else
		{
			TeamPanel* panel = new TeamPanel(getLobbyMenu(), this, PixelRect(20, teamPanels[i-1]->getRelativeRect().getBot() + 20, 140, 60), Team::get(i));
			addComponent(panel);
			teamPanels.push_back(panel);
		}
		teamPanels[i]->update(getLobbyMenu()->getPlayers()); // updaten
		teamPanels[i]->calcSize();
	}
}

LobbyMenu* TeamListPanel::getLobbyMenu() const
{
	return lobby;
}

void TeamListPanel::disableTeamButtons()
{
	for (unsigned int i = 0; i < teamPanels.size(); i++)
	{
		teamPanels[i]->disableTeamButton();
	}
}
