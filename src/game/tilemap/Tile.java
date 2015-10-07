package game.tilemap;

import java.awt.Color;

import game.tilemap.tiles.*;
import misc.Debug;

public abstract class Tile // TODO: extends Entity?
{
	public boolean isCollidable() { return true; } 
		// Collision between player and tile
	public boolean isStatic() { return true; }
		// needed for static rendering.
		// should return false if tile may move or change image
	public static Tile getByColorID(int colorID)
	{
		// TODO
		Debug.warn("Tile.getByColorID: TODO!! returns null");
		return null;
	}
}
