package network.lobby.packets.user;

import misc.Debug;
import player.property.Team;
import misc.compress.Compressor;
import network.lobby.packets.UserPacket;

public class TeamUserPacket extends UserPacket
{
	private int teamID;

	public TeamUserPacket(Team team)
	{
		teamID = team.getID();
	}

	public void assign(TeamUserPacket teamPacket)
	{
		Debug.warnIf(teamPacket == null, "TeamUserPacket.assign(null)");
		teamID = teamPacket.teamID;
	}


	public TeamUserPacket(TeamUserPacket packet)
	{
		teamID = packet.teamID;
	}

	@Override public byte getCID() { return Compressor.TEAM_USER_PACKET_CID; }
	@Override public byte[] compress()
	{
		return Compressor.compressInt(teamID);
	}

	public Team getTeam()
	{
		return Team.getByID(teamID);
	}
}
