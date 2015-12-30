package misc.math.pixel;

import misc.math.pixel.PixelPoint;

public class PixelPosition extends PixelPoint implements java.io.Serializable // used in MouseMoveEventPacket
{
	public PixelPosition()
	{
		super();
	}

	public PixelPosition(int x, int y)
	{
		super(x, y);
	}

	public PixelPosition(PixelPoint point)
	{
		this(point.getX(), point.getY());
	}

	public boolean equals(PixelPosition position)
	{
		return (getX() == position.getX() && getY() == position.getY());
	}

	public void add(PixelPosition position)
	{
		setX(getX() + position.getX());
		setY(getY() + position.getY());
	}

	public void subtract(PixelPosition position)
	{
		setX(getX() - position.getX());
		setY(getY() - position.getY());
	}

	public PixelPosition plus(PixelPosition position)
	{
		return new PixelPosition(getX() + position.getX(), getY() + position.getY());
	}

	public PixelPosition minus(PixelPosition position)
	{
		return new PixelPosition(getX() - position.getX(), getY() - position.getY());
	}

	public boolean inRect(PixelPosition pos, PixelSize size)
	{
		return getX() >= pos.getX()
			&& getX() <= pos.getX() + size.getX()
			&& getY() >= pos.getY()
			&& getY() <= pos.getY() + size.getY();
	}

	public boolean inRect(PixelRect rect)
	{
		return inRect(rect.getPosition(), rect.getSize());
	}
}
