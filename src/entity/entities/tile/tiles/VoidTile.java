package entity.entities.tile.tiles;

import entity.entities.tile.Tile;
import graphics.ImageFile;
import graphics.ImageID;

public class VoidTile extends Tile
{
	public VoidTile()
	{
		
	}

	@Override public ImageID getImageID()
	{
		return ImageFile.VOID_TILE.getImageID();
	}
}
