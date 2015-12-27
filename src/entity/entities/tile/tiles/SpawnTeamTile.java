package entity.entities.tile.tiles;

import misc.game.Team;
import entity.entities.tile.Tile;
import graphics.ImageFile;
import graphics.ImageID;

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

	@Override public ImageID getImageID()
	{
		return ImageFile.SPAWNTEAM_TILE.getImageID();
	}
}
