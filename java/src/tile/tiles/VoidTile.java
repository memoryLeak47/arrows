package tile.tiles;

import static core.Main.TILESIZE;
import tile.ExtendedTile;
import graphics.ImageFile;
import graphics.ImageID;
import graphics.animations.StaticAnimation;
import misc.math.game.GamePosition;
import misc.math.game.GameSize;

public class VoidTile extends ExtendedTile
{
	public VoidTile(GamePosition position)
	{
		super(position, new StaticAnimation(ImageFile.VOID_TILE.getImageID()));
	}
}
