package misc.math;

import misc.math.Point;

public class Size extends Point
{
	public Size()
	{
		super();
	}

	public Size(int x, int y)
	{
		super(x, y);
	}

	public Size(Point point)
	{
		this(point.getX(), point.getY());
	}
}
