package network.lobby.packets.user;

import game.Team;
import network.lobby.packets.UserPacket;

public class TeamUserPacket extends UserPacket
{
	private int teamID;

	public TeamUserPacket(Team team)
	{
		teamID = team.getID();
	}

	public TeamUserPacket(TeamUserPacket packet)
	{
		teamID = packet.teamID;
	}

	public Team getTeam()
	{
		return Team.getByID(teamID);
	}
}
