package misc.math;

public class Point
{
	private int x, y;

	public Point(int x, int y)
	{
		this.x = x;
		this.y = y;
	}

	public Point(Point point)
	{
		setX(point.getX());
		setY(point.getY());
	}

	public boolean equals(Point point)
	{
		return (getX() == point.getX() && getY() == point.getY());
	}

	public void add(Point point)
	{
		setX(getX() + point.getX());
		setY(getY() + point.getY());
	}

	public void subtract(Point point)
	{
		setX(getX() - point.getX());
		setY(getY() - point.getY());
	}

	public Point plus(Point point)
	{
		return new Point(getX() + point.getX(), getY() + point.getY());
	}

	public Point minus(Point point)
	{
		return new Point(getX() - point.getX(), getY() - point.getY());
	}

	public int getX() { return x; }
	public int getY() { return y; }
	public String toString() { return "X = " + getX() + "; Y = " + getY(); }

	public void setX(int x) { this.x = x; }
	public void setY(int y) { this.y = y; }
}
