package game;

import misc.Debug;

public enum Team
{
	TEAM0(0, "None"), TEAM1(1, "Red"), TEAM2(2, "Blue"), TEAM3(3, "Green"), TEAM4(4, "Yellow");

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
