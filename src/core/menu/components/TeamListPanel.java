package core.menu.components;

import java.util.LinkedList;

import core.menu.Menu;
import core.menu.ComponentContainer;
import core.menu.NetworkingMenu;
import core.menu.components.Panel;
import core.menu.components.TeamPanel;
import core.menu.menues.LobbyMenu;
import game.Team;
import misc.math.Rect;
import network.lobby.LobbyPlayer;

public class TeamListPanel extends Panel
{
	private LinkedList<LobbyPlayer> players;

	public TeamListPanel(ComponentContainer parent, Rect rect, LinkedList<LobbyPlayer> players)
	{
		super(parent, rect);

		this.players = players; // Verweis auf die Player, die angezeigt werden sollen
		
		getComponents().add(new TeamPanel(this, new Rect(20, 20, 140, 60), Team.TEAM0));
		getComponents().add(new TeamPanel(this, new Rect(20, 120, 140, 60), Team.TEAM1));
		getComponents().add(new TeamPanel(this, new Rect(20, 220, 140, 60), Team.TEAM2));
		getComponents().add(new TeamPanel(this, new Rect(20, 320, 140, 60), Team.TEAM3));
		getComponents().add(new TeamPanel(this, new Rect(20, 420, 140, 60), Team.TEAM4));
	}
}
