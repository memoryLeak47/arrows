package network.lobby.packets;

import misc.compress.*;
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

	@Override public String toString() { return "UserPacketWithID (" + packet + ", " + id + ")"; }

	public UserPacketWithID(CompressBuffer buffer)
	{
		packet = (UserPacket) buffer.cutByCID(buffer.cutByte());
		id = buffer.cutInt();
	}

	@Override public byte getCID() { return Compressor.USER_PACKET_WITH_ID_CID; }
	@Override public byte[] compress()
	{
		return Compressor.concat(new byte[][]{
			Compressor.compress(getUserPacket()),
			Compressor.compressInt(getID())
		});
	}
}
