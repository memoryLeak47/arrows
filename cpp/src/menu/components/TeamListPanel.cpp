#include "TeamListPanel.hpp"

#include "TeamPanel.hpp"
#include "../../player/property/Team.hpp"
#include "../../misc/Debug.hpp"

TeamListPanel::TeamListPanel(LobbyMenu* c, const PixelRect& r) : Panel(c, r)
{
	//createTeamPanels();
	update();
}

void TeamListPanel::createTeamPanels()
{
	for (int i = 0; i < Team::getAmount(); i++)
	{
		addComponent(new TeamPanel(this, PixelRect(20, 20+100*i, 140, 60), Team::get(i)));
	}
}

void TeamListPanel::update()
{
	// Formatieren der TeamPanels (nach unten rutschen, falls das obere Panel zu weit nach unten reicht)
	getComponents().clear();
	for (int i = 0; i < Team::getAmount(); i++) // für alle TeamPanels updaten + formatieren
	{
		if (i == 0)
			addComponent(new TeamPanel(this, PixelRect(20, 20+100*i, 140, 60), Team::get(i)));
		else
			addComponent(new TeamPanel(this, PixelRect(20, getComponents()[i-1]->getRect().getBot() + 20, 140, 60), Team::get(i)));
		((TeamPanel*) getComponents()[i])->update(getLobbyMenu()->getPlayers()); // updaten
		((Panel*) getComponents()[i])->calcSize();
	}
}

LobbyMenu* TeamListPanel::getLobbyMenu() const
{
	return (LobbyMenu*) getParent();
}
