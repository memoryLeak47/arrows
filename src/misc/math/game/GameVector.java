package misc.math.game;

public class GameVector
{
	private float x, y;

	public GameVector()
	{
		this(0, 0);
	}

	public GameVector(float x, float y)
	{
		this.x = x;
		this.y = y;
	}

	public GameVector(GameVector point)
	{
		setX(point.getX());
		setY(point.getY());
	}

	public void set(GameVector point)
	{
		setX(point.getX());
		setY(point.getY());
	}

	public void set(float x, float y)
	{
		setX(x);
		setY(y);
	}

	public boolean equals(GameVector point)
	{
		return (getX() == point.getX() && getY() == point.getY());
	}

	public void add(GameVector point)
	{
		setX(getX() + point.getX());
		setY(getY() + point.getY());
	}

	public void subtract(GameVector point)
	{
		setX(getX() - point.getX());
		setY(getY() - point.getY());
	}

	public GameVector plus(GameVector point)
	{
		return new GameVector(getX() + point.getX(), getY() + point.getY());
	}

	public GameVector minus(GameVector point)
	{
		return new GameVector(getX() - point.getX(), getY() - point.getY());
	}

	public GameVector times(float s)
	{
		return new GameVector(s*getX(), s*getY());
	}

	public void addX(float a)
	{
		setX(getX() + a);
	}

	public void addY(float a)
	{
		setY(getY() + a);
	}

	public void scale(float s)
	{
		setX(getX() * s);
		setY(getY() * s);
	}

	public void scaleX(float s)
	{
		setX(getX() * s);
	}

	public void scaleY(float s)
	{
		setY(getY() * s);
	}

	public void divide(float s)
	{
		scale(1.f/s);
	}

	public float getMagnitude()
	{
		return (float)Math.hypot(getX(), getY());
	}

	public float getX() { return x; }
	public float getY() { return y; }
	public String toString() { return "(" + getX() + "|" + getY() + ")"; }

	public void setX(float x) { this.x = x; }
	public void setY(float y) { this.y = y; }
}
