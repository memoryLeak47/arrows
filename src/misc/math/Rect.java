package misc.math;

import misc.math.Point;
import misc.math.Position;
import misc.math.Size;

public class Rect
{
	private Position position;
	private Size size;

	public Rect(Position position, Size size)
	{
		this.position = position;
		this.size = size;
	}

	public Rect(Rect rect)
	{
		setPosition(rect.getPosition());
		setSize(rect.getSize());
	}

	public Rect(int x, int y, int w, int h)
	{
		this(new Position(x, y), new Size(w, h));
	}

	public float distanceTo(Point point)
	{
		// TODO
		return 2;
	}

	public void setPosition(Point point) { position = new Position(point); }
	public void setSize(Point point) { size = new Size(point); }
	public void setLeft(int left) { getPosition().setX(left); }
	public void setTop(int top) { getPosition().setX(top); }
	public void setWidth(int width) { getSize().setX(width); }
	public void setHeight(int height) { getSize().setY(height); }

	public final int getBot() { return (getY() + getHeight()); }
	public final int getLeft() { return getX(); }
	public final int getRight() { return (getX() + getWidth()); }
	public final int getTop() { return getY(); }
	public int getX() { return getPosition().getX(); }
	public int getY() { return getPosition().getY(); }
	public int getWidth() { return getSize().getX(); }
	public int getHeight() { return getSize().getY(); }
	public Size getSize() { return size; }
	public Position getPosition() { return position; }
}
