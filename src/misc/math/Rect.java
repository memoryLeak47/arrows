package misc.math;

import misc.math.Point;
import misc.math.Position;
import misc.math.Size;

public class Rect
{
	private Position position;
	private Size size;

	public Rect(Position position, Size size)
	{
		this.position = position;
		this.size = size;
	}

	public Rect(Rect rect)
	{
		setPosition(rect.getPosition());
		setSize(rect.getSize());
	}

	public Rect(int x, int y, int w, int h)
	{
		this(new Position(x, y), new Size(w, h));
	}

	public float distanceTo(Point point)
	{
		// TODO
		return 2;
	}

	public void setPosition(Point point) { position = new Position(point); }
	public void setSize(Point point) { size = new Size(point); }

	public int getX() { return getPosition().getX(); }
	public int getY() { return getPosition().getY(); }
	public int getWidth() { return getSize().getX(); }
	public int getHeight() { return getSize().getY(); }
	public Size getSize() { return size; }
	public Position getPosition() { return position; }
}
