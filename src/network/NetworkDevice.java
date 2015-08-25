package network;

import java.net.*;

import network.game.packets.EventPacket;
import core.menu.menues.GameInterface;
import core.menu.menues.LobbyMenu;
import core.Main;
import static misc.Serializer.*;
import misc.Debug;

public abstract class NetworkDevice // server or client
{
	public static final short PORT = 4208;
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
		byte[] data = objectToByteArray(packet);
		DatagramPacket datagramPacket = new DatagramPacket(data, data.length, ip, PORT);
		try
		{
			socket.send(datagramPacket);
		} catch (Exception e) { Debug.quit("Failed to send data"); }
	}

	public void receive()
	{
		byte[] data = new byte[Packet.MAX_SIZE];
		DatagramPacket datagramPacket = new DatagramPacket(data, data.length);
		try
		{
			socket.receive(datagramPacket);
		} catch (Exception e) { Debug.quit("Failed to receive data"); }
		handlePacket((Packet) byteArrayToObject(data), datagramPacket.getAddress());
	}

	public abstract void handlePacket(Packet packet, InetAddress sender);
	public abstract void lobbyTick();
	public abstract void gameTick();
}
