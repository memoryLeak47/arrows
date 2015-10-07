package game;

import java.awt.Color;

import misc.Debug;

public enum Team
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

	public int getID() { return id; }
	public String getName() { return name; }
	public Color getColor() { return new Color(getColorID()); }
	public int getColorID() { return colorID; }
}
