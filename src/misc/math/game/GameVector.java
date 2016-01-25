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
		x = point.getX();
		y = point.getY();
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

	public GameVector timesX(float s)
	{
		return new GameVector(getX()*s, getY());
	}

	public GameVector timesY(float s)
	{
		return new GameVector(getX(), getY()*s);
	}

	public boolean equals(GameVector point)
	{
		return (getX() == point.getX() && getY() == point.getY());
	}

	public GameVector plus(GameVector point)
	{
		return new GameVector(getX() + point.getX(), getY() + point.getY());
	}

	public GameVector plusX(float f)
	{
		return new GameVector(getX() + f, getY());
	}

	public GameVector plusY(float f)
	{
		return new GameVector(getX(), getY() + f);
	}

	public GameVector minus(GameVector point)
	{
		return new GameVector(getX() - point.getX(), getY() - point.getY());
	}

	public GameVector times(float s)
	{
		return new GameVector(s*getX(), s*getY());
	}

	public GameVector divide(float s)
	{
		return new GameVector(getX()/s, getY()/s);
	}

	public float getMagnitude()
	{
		return (float) Math.hypot(getX(), getY());
	}

	public GameVector withMagnitude(float mag)
	{
		return normalize().times(mag);
	}

	public GameVector normalize()
	{
		float mag = getMagnitude();
		return new GameVector(getX() / mag, getY() / mag);
	}

	public GameVector rotate(float r)
	{
		return new GameVector(
			(float) (getX()*Math.cos(r) - getY()*Math.sin(r)),
			(float) (getX()*Math.sin(r) + getY()*Math.cos(r)));
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
}
