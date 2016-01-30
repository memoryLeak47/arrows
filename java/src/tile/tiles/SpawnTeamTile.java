package tile.tiles;

import static core.Main.TILESIZE;
import player.property.Team;
import tile.ExtendedTile;
import graphics.animations.StaticAnimation;
import graphics.ImageFile;
import graphics.ImageID;
import misc.math.game.GamePosition;
import misc.math.game.GameSize;

public class SpawnTeamTile extends ExtendedTile
{
	private Team team;

	public SpawnTeamTile(Team team, GamePosition position)
	{
		super(position, new StaticAnimation(ImageFile.SPAWNTEAM_TILE.getImageID()));
		setTeam(team);
	}

	// Setter
	public void setTeam(Team team) { this.team = team; }

	// getter
	public Team getTeam() { return team; }
}
