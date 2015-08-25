package core.menu.menues;

import java.util.LinkedList;
import java.net.InetAddress;

import core.menu.Menu;
import network.lobby.LobbyPlayer;
import misc.Debug;

public class LobbyMenu extends Menu
{
	// TODO
	public static final int TEAM_PHASE = 0;
	public static final int AVATAR_PHASE = 1;
	public static final int ATTRIBUTE_PHASE = 2;
 
	private int phase = TEAM_PHASE;

	private LinkedList<LobbyPlayer> players;

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
