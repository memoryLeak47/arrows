package core.menu.components;

import java.util.LinkedList;

import core.menu.components.Panel;
import core.menu.components.LobbyTeamPanel;
import core.menu.menues.LobbyMenu;
import core.menu.NetworkingMenu;
import core.menu.Menu;
import misc.math.Rect;
import network.lobby.LobbyPlayer;

public class TeamListPanel extends Panel
{
	private LinkedList<LobbyPlayer> players;

	public TeamListPanel(Menu menu, Rect rect, LinkedList<LobbyPlayer> players)
	{
		super(menu, rect);

		this.players = players; // Verweis auf die Player, die angezeigt werden sollen
		
		addComponent(new LobbyTeamPanel(getParentLobbyMenu(), new Rect(20, 20, 140, 60), "Team None"));
		addComponent(new LobbyTeamPanel(getParentLobbyMenu(), new Rect(20, 120, 140, 60), "Team Blue"));
		addComponent(new LobbyTeamPanel(getParentLobbyMenu(), new Rect(20, 220, 140, 60), "Team Red"));
		addComponent(new LobbyTeamPanel(getParentLobbyMenu(), new Rect(20, 320, 140, 60), "Team Green"));
		addComponent(new LobbyTeamPanel(getParentLobbyMenu(), new Rect(20, 420, 140, 60), "Team Yellow"));
		//calcSize();
		updateImage();
	}

	@Override public void updateImage()
	{
		super.updateImage();
	}

	// Wird aufgerufen, wenn sich die Konstellation eines Spielers verändert
	public void update()
	{

		//calcSize();
	}

	public LobbyMenu getParentLobbyMenu() { return (LobbyMenu) getParentMenu(); }
}
