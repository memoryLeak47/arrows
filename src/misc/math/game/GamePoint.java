package misc.math.game;

public class GamePoint
{
	private float x, y;

	public GamePoint()
	{
		this(0, 0);
	}

	public GamePoint(float x, float y)
	{
		this.x = x;
		this.y = y;
	}

	public GamePoint(GamePoint point)
	{
		setX(point.getX());
		setY(point.getY());
	}

	public boolean equals(GamePoint point)
	{
		return (getX() == point.getX() && getY() == point.getY());
	}

	public void add(GamePoint point)
	{
		setX(getX() + point.getX());
		setY(getY() + point.getY());
	}

	public void subtract(GamePoint point)
	{
		setX(getX() - point.getX());
		setY(getY() - point.getY());
	}

	public GamePoint plus(GamePoint point)
	{
		return new GamePoint(getX() + point.getX(), getY() + point.getY());
	}

	public GamePoint minus(GamePoint point)
	{
		return new GamePoint(getX() - point.getX(), getY() - point.getY());
	}

	public GamePoint times(float f)
	{
		return new GamePoint(getX()*f, getY()*f);
	}

	public float getX() { return x; }
	public float getY() { return y; }
	public String toString() { return "(" + getX() + "|" + getY() + ")"; }

	public void setX(float x) { this.x = x; }
	public void setY(float y) { this.y = y; }
}
