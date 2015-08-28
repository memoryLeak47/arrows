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
	private LinkedList<LobbyPlayer> players;

	public LobbyMenu()
	{
		getComponents().add(new Label(this, new Rect(300, 10, 100, 20), "Lobby"));
		getComponents().add(new Button(this, new Rect(100, 50, 200, 50), "Team None") // Button "Team None"
		{
			@Override public void onClick(int mouseButton)
			{
				teamPressed(0);
			}
		}); // Next Step Button
		getComponents().add(new Button(this, new Rect(100, 200, 200, 50), "Team Blue") // Button "Team Blue"
		{
			@Override public void onClick(int mouseButton)
			{
				teamPressed(1);
			}
		}); // Next Step Button
		getComponents().add(new Button(this, new Rect(100, 350, 200, 50), "Team Red") // Button "Team Red"
		{
			@Override public void onClick(int mouseButton)
			{
				teamPressed(2);
			}
		}); // Next Step Button
		getComponents().add(new Button(this, new Rect(100, 500, 200, 50), "Team Green") // Button "Team Green"
		{
			@Override public void onClick(int mouseButton)
			{
				teamPressed(3);
			}
		}); // Next Step Button
		getComponents().add(new Button(this, new Rect(1000, 600, 200, 60), "Next Step")
		{
			@Override public void onClick(int mouseButton)
			{
				lockPressed();
			}
		}); // Next Step Button

		getComponents().add(new Button(this, new Rect(1000, 100, 200, 140), "Map Placeholder")
		{
			@Override public void onClick(int mouseButton)
			{
				mapPressed();
			}
		}); // Next Step Button
		
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

	public abstract void lockPressed();
	public abstract void teamPressed(int team);
	public abstract void mapPressed();
	@Override public boolean isFullscreen() { return true; }
}
