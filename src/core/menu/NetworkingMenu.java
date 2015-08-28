package core.menu;

import java.net.InetAddress;

import core.Main;
import network.Packet;

public abstract class NetworkingMenu extends Menu
// menu which interacts with network
{
	public static final int TEAM_NONE = 0;
	public static final int TEAM_BLUE = 1;
	public static final int TEAM_RED = 2;
	public static final int TEAM_GREEN = 3;
	public static final int TEAM_YELLOW = 4;

	public NetworkingMenu()
	{
		Main.getNetworkDevice().setMenu(this); // when receiving a packet give it to this.handlePacket(...)
	}

	public abstract void handlePacket(Packet packet, InetAddress ip); // networkDevice will call this when a packet was received
}
