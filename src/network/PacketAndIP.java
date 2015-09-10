package network;

import java.net.InetAddress;

import network.Packet;

public class PacketAndIP
{	
	private Packet packet;
	private InetAddress ip;

	public PacketAndIP(Packet packet, InetAddress ip)
	{
		this.packet = packet;
		this.ip = ip;
	}

	// Getter
	public Packet getPacket() { return packet; }
	public InetAddress getIP() { return ip; }
}
