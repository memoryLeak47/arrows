package core.menu.components;

import java.util.LinkedList;

import core.menu.Menu;
import core.menu.ComponentContainer;
import core.menu.NetworkingMenu;
import core.menu.MenuComponent;
import core.menu.components.Panel;
import core.menu.components.TeamPanel;
import core.menu.menues.LobbyMenu;
import game.Team;
import misc.math.Rect;
import network.lobby.LobbyPlayer;

public class TeamListPanel extends Panel
{
	public TeamListPanel(ComponentContainer parent, Rect rect)
	{
		super(parent, rect);

		getComponents().add(new TeamPanel(this, new Rect(20, 20, 140, 60), Team.TEAM0));
		getComponents().add(new TeamPanel(this, new Rect(20, 120, 140, 60), Team.TEAM1));
		getComponents().add(new TeamPanel(this, new Rect(20, 220, 140, 60), Team.TEAM2));
		getComponents().add(new TeamPanel(this, new Rect(20, 320, 140, 60), Team.TEAM3));
		getComponents().add(new TeamPanel(this, new Rect(20, 420, 140, 60), Team.TEAM4));
		update(); // erstellt die nötigen Player icons, etc...
	}

	// aktualisiert die PlayerIcons; Wird von den LobbyMenüs aufgerufen
	public void update()
	{
		// Formatieren der TeamPanels (nach unten rutschen, falls das obere Panel zu weit nach unten reicht)
		for (int i = 0; i < getComponents().size(); i++) // für alle TeamPanels updaten + formatieren
		{
			((TeamPanel) getComponents().get(i)).update(getPlayers()); // updaten
			((Panel) getComponents().get(i)).calcSize();
			if (i != 0) // Das oberste Panel, wird nie nach unten gerückt, weil das ja logisch ist
			{
				getComponents().get(i).setPosition(20, getComponents().get(i-1).getBot() + 20);
			}
		}
	}

	private LinkedList<LobbyPlayer> getPlayers()
	{
		return ((LobbyMenu) getParent()).getPlayers();
	}
}
