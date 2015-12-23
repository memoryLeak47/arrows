package misc.math;

public class TilePosition
{
	int x, y;

	public TilePosition(int x, int y)
	{
		this.x = x;
		this.y = y;
	}

	public int getX() { return x; }
	public int getY() { return y; }

	public Position toPosition() { return new Position(x*60, y*60); } // TODO insert TILESIZE
}
