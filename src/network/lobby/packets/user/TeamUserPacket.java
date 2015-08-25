package network.lobby.packets.user;

import network.lobby.packets.UserPacket;

public class TeamUserPacket extends UserPacket
{
	private int team;

	public TeamUserPacket(int value)
	{
		team = value;
	}

	public TeamUserPacket(TeamUserPacket packet)
	{
		team = packet.getTeam();
	}

	public int getTeam()
	{
		return team;
	}
}
