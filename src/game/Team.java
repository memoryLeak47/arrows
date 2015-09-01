package game;

import misc.Debug;

public enum Team
{
	TEAM0(0, "NONE"), TEAM1(1, "RED"), TEAM2(2, "BLUE"), TEAM3(3, "GREEN"), TEAM4(4, "YELLOW");

	private int id;
	private String name;

	private Team(int id, String name)
	{
		this.id = id;
		this.name = name;
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
		Debug.quit("team id " + id + " in Team.getByID");
		return null;
	}

	public int getID() { return id; }
	public String getName() { return name; }
}
