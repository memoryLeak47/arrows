package core.menu.menues;

import java.util.LinkedList;
import java.net.InetAddress;

import core.Main;
import core.menu.NetworkingMenu;
import core.menu.components.*;
import network.lobby.LobbyPlayer;
import network.Packet;
import misc.Debug;
import misc.math.Rect;

public abstract class LobbyMenu extends NetworkingMenu
{
	public static final int TEAM_PHASE = 0;
	public static final int AVATAR_PHASE = 1;
	public static final int ATTRIBUTE_PHASE = 2;
 
	private int phase;
	private LinkedList<LobbyPlayer> players; // Bluemi: protected -> private; added setter
	private TeamListPanel teamListPanel; // Nicht zwingend nötig, nur einfacherer Zugriff, da nicht über index

	public LobbyMenu()
	{
		getComponents().add(new Label(this, new Rect(300, 10, 100, 20), "Lobby"));

		teamListPanel = new TeamListPanel(this, new Rect(100, 100, 600, 600), getPlayers());
		getComponents().add(teamListPanel);

		getComponents().add(new Button(this, new Rect(1000, 600, 200, 60), "Next Step")
		{
			@Override public void onClick(int mouseButton)
			{
				lockPressed();
			}
		}); // Team Yellow Button

		getComponents().add(new Button(this, new Rect(1000, 100, 200, 140), "Map Placeholder")
		{
			@Override public void onClick(int mouseButton)
			{
				mapPressed();
			}
		}); // Map Placeholder
		
		phase = TEAM_PHASE;
		players = new LinkedList<LobbyPlayer>();
		updateComponents();
	}

	public final void addPlayer(LobbyPlayer player)
	{
		if (phase == TEAM_PHASE)
		{
			players.add(player);
		}
		else
		{
			Debug.quit("LobbyMenu.addPlayer: called while not in phase \"TEAM_PHASE\"");
		}
	}

	public final void updateComponents() // sets all components to the right place, sets all componnt-propertiers, called by any menu changing action
	{
		
	}

	public final void removePlayer(int id)
	{
		players.remove(id);
	}

	protected abstract LobbyPlayer getLocalPlayer();

	public abstract void lockPressed();
	public abstract void teamPressed(int team);
	public abstract void mapPressed();
	public abstract void nextPhase();

	protected int getPhase() { return phase; }
	protected LinkedList<LobbyPlayer> getPlayers() { return players; }
	@Override public boolean isFullscreen() { return true; }

	protected void setPlayers(LinkedList<LobbyPlayer> players) 
	{ 
		this.players = players; 
		teamListPanel.update();
	}
}
