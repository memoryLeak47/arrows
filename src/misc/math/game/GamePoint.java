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

	public GamePoint(GamePoint pofloat)
	{
		setX(pofloat.getX());
		setY(pofloat.getY());
	}

	public boolean equals(GamePoint pofloat)
	{
		return (getX() == pofloat.getX() && getY() == pofloat.getY());
	}

	public void add(GamePoint pofloat)
	{
		setX(getX() + pofloat.getX());
		setY(getY() + pofloat.getY());
	}

	public void subtract(GamePoint pofloat)
	{
		setX(getX() - pofloat.getX());
		setY(getY() - pofloat.getY());
	}

	public GamePoint plus(GamePoint pofloat)
	{
		return new GamePoint(getX() + pofloat.getX(), getY() + pofloat.getY());
	}

	public GamePoint minus(GamePoint pofloat)
	{
		return new GamePoint(getX() - pofloat.getX(), getY() - pofloat.getY());
	}

	public float getX() { return x; }
	public float getY() { return y; }
	public String toString() { return "(" + getX() + "|" + getY() + ")"; }

	public void setX(float x) { this.x = x; }
	public void setY(float y) { this.y = y; }
}
