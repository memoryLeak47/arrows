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
		
		phase = TEAM_PHASE;
		players = new LinkedList<LobbyPlayer>();
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

	public final void removePlayer(int id)
	{
		players.remove(id);
	}

	@Override public boolean isFullscreen() { return true; }
}
