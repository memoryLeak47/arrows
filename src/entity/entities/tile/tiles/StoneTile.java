package entity.entities.tile.tiles;

import static core.Main.TILESIZE;
import entity.entities.tile.Tile;
import misc.Debug;
import graphics.ImageFile;
import graphics.ImageID;
import graphics.animations.StaticAnimation;
import misc.math.game.GamePosition;
import misc.math.game.GameSize;

public class StoneTile extends Tile
{
	public StoneTile(GamePosition position)
	{
		super(position, new GameSize(TILESIZE, TILESIZE), new StaticAnimation(ImageFile.STONE_TILE.getImageID()));
	}
}
