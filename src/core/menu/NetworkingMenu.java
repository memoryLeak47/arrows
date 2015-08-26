package core.menu;

import java.net.InetAddress;

import network.Packet;

public abstract class NetworkingMenu extends Menu
{
	public abstract void handlePacket(Packet packet, InetAddress ip);
}
