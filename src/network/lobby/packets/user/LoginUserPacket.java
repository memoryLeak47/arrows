package network.lobby.packets.user;

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

	public LoginUserPacket(LoginUserPacket packet)
	{
		name = new String(packet.getName());
		rank = packet.getRank();
	}

	public String getName() { return name; }
	public int getRank() { return rank; }
}
