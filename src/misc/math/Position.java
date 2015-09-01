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

	public boolean equals(Position position)
	{
		return (getX() == position.getX() && getY() == position.getY());
	}

	public void add(Position position)
	{
		setX(getX() + position.getX());
		setY(getY() + position.getY());
	}

	public void subtract(Position position)
	{
		setX(getX() - position.getX());
		setY(getY() - position.getY());
	}

	public Position plus(Position position)
	{
		return new Position(getX() + position.getX(), getY() + position.getY());
	}

	public Position minus(Position position)
	{
		return new Position(getX() - position.getX(), getY() - position.getY());
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
