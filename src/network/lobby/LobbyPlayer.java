package network.lobby;

import java.net.InetAddress;

import network.lobby.packets.UserPacket;
import network.lobby.packets.user.*;

public class LobbyPlayer
{
	private InetAddress ip;

	private String username;
	private int rank;
	private boolean locked;
	private int avatar;
	private int team;
	private int[] skills;
	private int[] items;

	public final void applyUserPacket(UserPacket packet)
	{
		// TODO
	}

	public InetAddress getIP() { return ip; }
	public String getName() { return username; }
	public int getRank() { return rank; }
	// more getters
}
