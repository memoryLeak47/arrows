package entity.entities.tile.tiles;

import static core.Main.TILESIZE;
import misc.game.Team;
import entity.entities.tile.Tile;
import graphics.animations.StaticAnimation;
import graphics.ImageFile;
import graphics.ImageID;
import misc.math.game.GamePosition;
import misc.math.game.GameSize;

public class SpawnTeamTile extends Tile
{
	private Team team;

	public SpawnTeamTile(Team team, GamePosition position)
	{
		super(position, new GameSize(TILESIZE, TILESIZE), new StaticAnimation(ImageFile.SPAWNTEAM_TILE.getImageID()));
		setTeam(team);
	}

	// Setter
	public void setTeam(Team team) { this.team = team; }

	// Getter
	public Team getTeam() { return team; }
}
