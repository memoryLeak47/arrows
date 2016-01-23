package network.lobby.packets.user;

import misc.compress.Compressor;
import network.lobby.packets.UserPacket;

public class LoginUserPacket extends UserPacket
{
	private String name;
	private int rank;

	public LoginUserPacket(String name, int rank)
	{
		this.name = name;
		this.rank = rank;
	}

	public void assign(LoginUserPacket loginPacket)
	{
		this.name = loginPacket.name;
		this.rank = loginPacket.rank;
	}

	public LoginUserPacket(LoginUserPacket packet)
	{
		name = new String(packet.getName());
		rank = packet.getRank();
	}

	@Override public byte getCID() { return Compressor.LOGIN_USER_PACKET_CID; }
	@Override public byte[] compress()
	{
		return Compressor.concat(new byte[][]{
			Compressor.compressString(getName()),
			Compressor.compressInt(getRank())});
	}

	public String getName() { return name; }
	public int getRank() { return rank; }
}
