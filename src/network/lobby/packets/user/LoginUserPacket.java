package network.lobby.packets.user;

import network.lobby.packets.UserPacket;

public class LoginUserPacket extends UserPacket
{
	private String name;
	private int rank;

	public String getName() { return name; }
	public int getRank() { return rank; }
}
