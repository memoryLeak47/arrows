package entity.tile.tiles;

import entity.tile.Tile;

public class VoidTile extends Tile
{
	public VoidTile()
	{
		
	}

	@Override public boolean isCollidable() { return false; }
}
