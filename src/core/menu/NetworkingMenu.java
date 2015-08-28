package core.menu;

import java.net.InetAddress;

import core.Main;
import network.Packet;

public abstract class NetworkingMenu extends Menu
// menu which interacts with network
{
	public NetworkingMenu()
	{
		Main.getNetworkDevice().setMenu(this); // when receiving a packet give it to this.handlePacket(...)
	}

	protected void send(Packet packet, InetAddress ip)
	{
		Main.getNetworkDevice().send(packet, ip);
	}

	public abstract void handlePacket(Packet packet, InetAddress ip); // networkDevice will call this when a packet was received
}
