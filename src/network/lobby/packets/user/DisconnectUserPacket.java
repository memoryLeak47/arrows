package network.lobby.packets.user;

import misc.compress.Compressor;
import network.lobby.packets.UserPacket;

public class DisconnectUserPacket extends UserPacket
{
	@Override public byte getCID() { return Compressor.DISCONNECT_USER_PACKET_CID; }
	@Override public byte[] compress() { return new byte[]{}; }
}
