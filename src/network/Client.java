package network;

import java.net.*;
import java.lang.Thread;

import network.NetworkDevice;
import network.packets.EventPacket;
import network.Packet;

public class Client extends NetworkDevice
{
	private DatagramSocket socket;

	public void onEvent(EventPacket event)
	{
		// sends to Server
	}

	@Override public void handlePacket(Packet packet, InetAddress ip)
	{
		
	}

	@Override public void lobbyTick()
	{
		// TODO
	}

	@Override public void gameTick() {}

}
