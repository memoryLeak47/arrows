package menu.menues;

import java.net.InetAddress;

import menu.menues.GameInterface;
import misc.Debug;
import network.Packet;
import network.game.packets.EventPacket;

public class ServerGameInterface extends GameInterface
{
	
	@Override public void handlePacket(Packet packet, InetAddress ip)
	{
		if (packet instanceof EventPacket)
		{
			// TODO
		}
		else
		{
			Debug.log("ServerGameInterface got non-EventPacket"); // ignore packet
		}
	}
}
