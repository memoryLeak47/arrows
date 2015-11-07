package game.tilemap.tiles;

import game.Team;
import game.tilemap.Tile;

public class SpawnTeamTile extends Tile
{
	private Team team;

	public SpawnTeamTile(Team team)
	{
		setTeam(team);
	}

	// Setter
	public void setTeam(Team team) { this.team = team; }

	// Getter
	public Team getTeam() { return team; }
}
