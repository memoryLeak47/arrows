package network;

import java.net.*;

import network.game.packets.EventPacket;
import core.menu.menues.GameInterface;
import core.menu.menues.LobbyMenu;
import core.Main;

public abstract class NetworkDevice // server or client
{
	private DatagramSocket socket;

	public void onEvent(EventPacket event)
	{
		// TODO
	}

	public final void tick() // calledby Main.run()
	{
		if (Main.getActiveMenu() instanceof GameInterface)
		{
			gameTick();
		}
		else if (Main.getActiveMenu() instanceof LobbyMenu)
		{
			lobbyTick();
		}
		else
		{
			System.out.println("ERROR: NetworkDevice.tick() - NetworkDevice created, but Menu != GameInterface and Menu != LobbyMenu");
			System.exit(1);
		}
	}

	public void send(Packet packet, InetAddress ip)
	{
		// TODO
	}

	public void receive()
	{
		// TODO
		//handlePacket('received Packet', 'Ip of sender');
	}

	public abstract void handlePacket(Packet packet, InetAddress sender);
	public abstract void lobbyTick();
	public abstract void gameTick();
}
