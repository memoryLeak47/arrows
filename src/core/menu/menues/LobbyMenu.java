package core.menu.menues;

import java.util.LinkedList;
import java.net.InetAddress;

import core.Main;
import core.menu.NetworkingMenu;
import core.menu.components.*;
import game.Team;
import misc.Debug;
import misc.math.Rect;
import network.lobby.LobbyPlayer;
import network.Packet;

public abstract class LobbyMenu extends NetworkingMenu
{
	public static final int TEAM_PHASE = 0;
	public static final int AVATAR_PHASE = 1;
	public static final int ATTRIBUTE_PHASE = 2;
 
	private int phase;
	protected Button lockButton; // Verweiß auf den NextStep/LockIn Button
	private LinkedList<LobbyPlayer> players; // Bluemi: protected -> private; added setter
	private TeamListPanel teamListPanel; // Nicht zwingend nötig, nur einfacherer Zugriff, da nicht über index

	public LobbyMenu()
	{
		getComponents().add(new Label(this, new Rect(300, 10, 100, 20), "Lobby"));

		teamListPanel = new TeamListPanel(this, new Rect(100, 100, 600, 600));
		getComponents().add(teamListPanel);

		lockButton = new Button(this, new Rect(1000, 600, 200, 60), "Next Step")
		{
			@Override public void onClick(int mouseButton)
			{
				lockPressed();
			}
		}; // Lock-Button
		getComponents().add(lockButton);

		getComponents().add(new Button(this, new Rect(1000, 100, 200, 140), "Map Placeholder")
		{
			@Override public void onClick(int mouseButton)
			{
				mapPressed();
			}
		}); // Map Placeholder
		
		phase = TEAM_PHASE;
		players = new LinkedList<LobbyPlayer>();
	}

	// Wird von unterklassen aufgerufen, nachdem ein Spieler bearbeitet wurde
	protected final void updatePlayerIcons()
	{
		teamListPanel.update();
	}

	protected abstract LobbyPlayer getLocalPlayer();

	public abstract void lockPressed();
	public abstract void teamPressed(Team team);
	public abstract void mapPressed();
	public abstract void nextPhase();

	protected int getPhase() { return phase; }
	public LinkedList<LobbyPlayer> getPlayers() { return players; } // public damit TeamListPanel darauf zugreifen kann

	protected void setPlayers(LinkedList<LobbyPlayer> players) 
	{ 
		this.players = players; 
	}
}
