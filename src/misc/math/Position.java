package misc.math;

import misc.math.Point;

public class Position extends Point
{
	public Position(int x, int y)
	{
		super(x, y);
	}

	public Position(Point point)
	{
		this(point.getX(), point.getY());
	}

	public boolean inRect(Position pos, Size size)
	{
		return getX() >= pos.getX()
			&& getX() <= pos.getX() + size.getX()
			&& getY() >= pos.getY()
			&& getY() <= pos.getY() + size.getY();
	}

	public boolean inRect(Rect rect)
	{
		return inRect(rect.getPosition(), rect.getSize());
	}
}
