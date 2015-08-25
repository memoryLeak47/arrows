package network.packets.lobby;

import network.packets.LobbyPacket;

public class UserLobbyPacket extends LobbyPacket
{
	private String name;
	private int rank;

	public String getName() { return name; }
	public int getRank() { return rank; }
}
