package entity.entities.tile.tiles;

import static core.Main.TILESIZE;
import entity.entities.tile.ExtendedTile;
import graphics.ImageFile;
import graphics.ImageID;
import graphics.animations.StaticAnimation;
import misc.math.game.GamePosition;
import misc.math.game.GameSize;

public class VoidTile extends ExtendedTile
{
	public VoidTile(GamePosition position)
	{
		super(position, new GameSize(TILESIZE, TILESIZE), new StaticAnimation(ImageFile.VOID_TILE.getImageID()));
	}
}
