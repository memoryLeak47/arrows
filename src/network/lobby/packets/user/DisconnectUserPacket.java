package network.lobby.packets.user;

import misc.compress.*;
import network.lobby.packets.UserPacket;

public class DisconnectUserPacket extends UserPacket
{
	public DisconnectUserPacket() {}
	public DisconnectUserPacket(CompressBuffer buffer) {}

	@Override public byte getCID() { return Compressor.DISCONNECT_USER_PACKET_CID; }
	@Override public byte[] compress() { return new byte[]{}; }
}
