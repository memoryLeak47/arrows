package network;

import java.net.*;

import menu.NetworkingMenu;
import core.Main;
import static misc.Serializer.*;
import misc.Debug;
import network.game.packets.EventPacket;

public class NetworkDevice
{
	public static final short PORT = 4208;
	private DatagramSocket socket;
	private NetworkingMenu menu; // when packet was received, menu.handlePacket(...) will take care of the packet

	public NetworkDevice()
	{
		try
		{
			socket = new DatagramSocket(PORT); // create socket
		} catch (Exception e) { Debug.quit("can't create socket"); }
	}

	public void send(Packet packet, InetAddress ip) // send packet to ip
	{
		byte[] data = objectToByteArray(packet); // serialize packet -> data
		DatagramPacket datagramPacket = new DatagramPacket(data, data.length, ip, PORT); // create datagramPacket
		try
		{
			socket.send(datagramPacket); // send
		} catch (Exception e) { Debug.quit("Failed to send data"); }
	}

	public void receive() // called by Main.run() permanently, receives packets and gives them to menu.handlePacket(...)
	{
		byte[] data = new byte[Packet.MAX_SIZE]; // create byte[] data
		DatagramPacket datagramPacket = new DatagramPacket(data, data.length); // create DatagramPacket
		try
		{
			socket.receive(datagramPacket); // receive packet
		} catch (Exception e) { Debug.quit("Failed to receive data"); }

		if (menu != null) // if there is a target menu
		{
			menu.receivePacket((Packet) byteArrayToObject(data), datagramPacket.getAddress()); // let it handle the packet
		}
	}

	public void setMenu(NetworkingMenu menu) { this.menu = menu; } // set target menu
}
