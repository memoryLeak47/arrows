package misc.math.menu;

public class MenuPoint
{
	private int x, y;

	public MenuPoint()
	{
		this(0, 0);
	}

	public MenuPoint(int x, int y)
	{
		this.x = x;
		this.y = y;
	}

	public MenuPoint(MenuPoint point)
	{
		setX(point.getX());
		setY(point.getY());
	}

	public boolean equals(MenuPoint point)
	{
		return (getX() == point.getX() && getY() == point.getY());
	}

	public void add(MenuPoint point)
	{
		setX(getX() + point.getX());
		setY(getY() + point.getY());
	}

	public void subtract(MenuPoint point)
	{
		setX(getX() - point.getX());
		setY(getY() - point.getY());
	}

	public MenuPoint plus(MenuPoint point)
	{
		return new MenuPoint(getX() + point.getX(), getY() + point.getY());
	}

	public MenuPoint minus(MenuPoint point)
	{
		return new MenuPoint(getX() - point.getX(), getY() - point.getY());
	}

	public int getX() { return x; }
	public int getY() { return y; }
	public String toString() { return "(" + getX() + "|" + getY() + ")"; }

	public void setX(int x) { this.x = x; }
	public void setY(int y) { this.y = y; }
}
