package core.menu;

import java.net.InetAddress;

import network.Packet;

public abstract class NetworkingMenu extends Menu
// menu which interacts with network
{
	public abstract void handlePacket(Packet packet, InetAddress ip); // networkDevice will call this when a packet was received
}
