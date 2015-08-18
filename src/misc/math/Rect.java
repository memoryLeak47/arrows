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

	public void setPosition(Point point)
	{
		position = new Position(point);
	}

	public void setSize(Point point)
	{
		size = new Size(point);
	}

	public Size getSize() { return size; }
	public Position getPosition() { return position; }

	public float distanceTo(Point point)
	{
		// TODO
		return 2;
	}
}
