package entity.entities.tile.tiles;

import entity.entities.tile.Tile;
import misc.Debug;
import graphics.ImageFile;
import graphics.ImageID;

public class StoneTile extends Tile
{
	@Override public ImageID getImageID()
	{
		return ImageFile.STONE_TILE.getImageID();
	}
}
