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
		this.position = new Position(position);
		this.size = new Size(size);
	}

	public Rect(Rect rect)
	{
		this(rect.getPosition(), rect.getSize());
	}

	public Rect(int x, int y, int w, int h)
	{
		this(new Position(x, y), new Size(w, h));
	}

	public Rect()
	{
		this(new Position(0,0), new Size(0,0));
	}

	public float distanceTo(Point point)
	{
		// TODO
		return 2;
	}

	public void centerX(int width)
	{
		int left;
		left = (int)((width - this.getWidth()) / 2);
		setLeft(left);
	}

	public void centerY(int height)
	{
		int top;
		top = (int)((height - this.getHeight()) / 2);
		setTop(top);
	}

	// zentriert die Komponente im übergebenen Rectangle
	public void center(Rect rect)
	{
		centerX(rect);
		centerY(rect);
	}

	// zentriert die Komponente im übergebenen Rectangle in X-Richtung
	public void centerX(Rect rect)
	{
		int left;
		left = (int)((rect.getWidth() - this.getWidth()) / 2);
		setLeft(rect.getLeft() + left);
	}

	// zentriert die Komponente im übergebenen Rectangle in Y-Richtung
	public void centerY(Rect rect)
	{
		int top;
		top = (int)((rect.getHeight() - this.getHeight()) / 2);
		setTop(rect.getTop() + top);
	}

	public boolean equals(Rect rect)
	{
		return (getPosition().equals(rect.getPosition()) && getSize().equals(rect.getSize()));
	}

	public void setPosition(Point point) { position = new Position(point); }
	public void setPosition(int x, int y) { position = new Position(x, y); }
	public void setSize(Point point) { size = new Size(point); }
	public void setSize(int x, int y) { size = new Size(x, y); }
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
