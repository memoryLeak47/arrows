package misc.math.game;

import misc.compress.*;

public class GameVector implements Compressable
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

	public GameVector(CompressBuffer buffer)
	{
		x = buffer.cutFloat();
		y = buffer.cutFloat();
	}

	@Override public byte getCID() { return Compressor.GAME_VECTOR_CID; }
	@Override public byte[] compress()
	{
		byte[] bytes = new byte[8];
		byte[] x = Compressor.compressFloat(getX());
		byte[] y = Compressor.compressFloat(getY());
		for (int i = 0; i < 4; i++)
		{
			bytes[i] = x[i];
			bytes[i+4] = y[i];
		}
		return bytes;
	}

	public void setMagnitude(float m)
	{
		float mag = getMagnitude();
		setX(getX()/mag*m);
		setY(getY()/mag*m);
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

	public void rotate(float r)
	{
		float x = getX();
		setX((float) (getX()*Math.cos(r) - getY()*Math.sin(r)));
		setY((float) (x*Math.sin(r) + getY()*Math.cos(r)));
	}

	public static GameVector getFromTo(GameVector vec1, GameVector vec2)
	{
		return new GameVector(vec2.getX() - vec1.getX(), vec2.getY() - vec1.getY());
	}

	public static GameVector getFromTo(float x1, float y1, float x2, float y2)
	{
		return new GameVector(x2 - x1, y2 - y1);
	}

	public float getX() { return x; }
	public float getY() { return y; }
	public String toString() { return "(" + getX() + "|" + getY() + ")"; }

	public void setX(float x) { this.x = x; }
	public void setY(float y) { this.y = y; }
}
