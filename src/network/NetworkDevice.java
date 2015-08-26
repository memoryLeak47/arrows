package network;

import java.net.*;

import network.game.packets.EventPacket;
import core.menu.NetworkingMenu;
import core.Main;
import static misc.Serializer.*;
import misc.Debug;

public class NetworkDevice
{
	public static final short PORT = 4208;
	private DatagramSocket socket;
	private NetworkingMenu menu;

	public NetworkDevice()
	{
		try
		{
			socket = new DatagramSocket();
		} catch (Exception e) { Debug.quit("can't create socket"); }
	}

	public NetworkDevice(NetworkingMenu menu)
	{
		this();
		setMenu(menu);
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
		menu.handlePacket((Packet) byteArrayToObject(data), datagramPacket.getAddress());
	}

	public void setMenu(NetworkingMenu menu) { this.menu = menu; }
}
