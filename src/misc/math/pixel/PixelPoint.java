package misc.math.pixel;

public class PixelPoint
{
	private int x, y;

	public PixelPoint()
	{
		this(0, 0);
	}

	public PixelPoint(int x, int y)
	{
		this.x = x;
		this.y = y;
	}

	public PixelPoint(PixelPoint point)
	{
		setX(point.getX());
		setY(point.getY());
	}

	public boolean equals(PixelPoint point)
	{
		return (getX() == point.getX() && getY() == point.getY());
	}

	protected void add(PixelPoint point)
	{
		setX(getX() + point.getX());
		setY(getY() + point.getY());
	}

	protected void subtract(PixelPoint point)
	{
		setX(getX() - point.getX());
		setY(getY() - point.getY());
	}

	public PixelPoint plus(PixelPoint point)
	{
		return new PixelPoint(getX() + point.getX(), getY() + point.getY());
	}

	public PixelPoint minus(PixelPoint point)
	{
		return new PixelPoint(getX() - point.getX(), getY() - point.getY());
	}

	public int getX() { return x; }
	public int getY() { return y; }
	public String toString() { return "(" + getX() + "|" + getY() + ")"; }

	protected void setX(int x) { this.x = x; }
	protected void setY(int y) { this.y = y; }
}
