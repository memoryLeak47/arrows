package game;

public abstract class Tile // TODO: extends Entity?
{
	public boolean isCollidable() { return true; } 
		// Collision between player and tile
	public boolean isStatic() { return true; }
		// needed for static rendering.
		// should return false if tile may move or change image
}
