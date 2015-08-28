package network.lobby.packets;

import network.Packet;
import network.lobby.packets.UserPacket;

public class UserPacketWithID extends Packet// sent from server to client to give UserPackets from clients to the other clients
{
	private UserPacket packet;
	private int id;

	public UserPacketWithID(UserPacket packet, int id)
	{
		this.packet = packet; // set per reference
		this.id = id;
	}

	public UserPacket getUserPacket() { return packet; }
	public int getID() { return id; }
}
