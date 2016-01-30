package player.property;

import java.awt.Color;
import java.util.Arrays;

import misc.Debug;
import misc.compress.*;

public enum Team implements Compressable
{
	TEAM0(0, "None", "666666"),
	TEAM1(1, "Red", "ff0000"),
	TEAM2(2, "Blue", "0000ff"),
	TEAM3(3, "Green", "00ff00"),
	TEAM4(4, "Yellow", "ffff00");

	private int id;
	private String name;
	private int colorID;

	private Team(int id, String name, String colorString)
	{
		this.id = id;
		this.name = name;
		this.colorID = Integer.parseInt(colorString, 16);
	}

	public boolean isTeamFriendly(Team team)
	{
		if (this == TEAM0 || team == TEAM0)
			return false;
		return this == team;
	}

	public static Team getByID(int id)
	{
		for (Team team : Team.values())
		{
			if (team.getID() == id)
			{
				return team;
			}
		}
		Debug.error("team id " + id + " in Team.getByID");
		return null;
	}

	@Override public byte getCID() { return Compressor.TEAM_CID; }
	@Override public byte[] compress()
	{
		return new byte[]{(byte) Arrays.asList(Team.values()).indexOf(this)};
	}

	public static Team cut(CompressBuffer buffer)
	{
		byte b = buffer.cutByte();
		return Team.values()[(int) b];
	}


	public int getID() { return id; }
	public String getName() { return name; }
	public Color getColor() { return new Color(getColorID()); }
	public int getColorID() { return colorID; }
}
