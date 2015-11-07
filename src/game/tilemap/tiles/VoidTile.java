package game.tilemap.tiles;

import game.tilemap.Tile;

public class VoidTile extends Tile
{
	public VoidTile()
	{
		
	}

	@Override public boolean isCollidable() { return false; }
}
